/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:39:11 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/16 20:35:20 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "minishell.h"

void	ft_exec(t_pnode *node, t_data *data);

//creates pipe or opens /dev/null and sets the nodes' input/output fd's
//returns 1 on success, 0 on failure
static int	pipe_next(t_pnode *node, t_data *data)
{
	int		pipe_fd[2];
	t_pnode	*next_next;

	next_next = node->output->output;
	if (!next_next || next_next->input[1])
	{
		node->output_fd = open("/dev/null", O_WRONLY);
		return (1);
	}
	else if (next_next->type == Pipe)
		return ((int)run_command(node->output, data));
	if (pipe(pipe_fd))
		return (0);
	node->output_fd = pipe_fd[1];
	next_next->input_fd = pipe_fd[0];
	return (1);
}

//creates pipes or opens files if needed and sets the node's output fd
//returns 1 on success and 0 on failure
int	output_handler(t_pnode *node, t_data *data)
{
	if (node->output->type == Pipe)
	{
		if (!pipe_next(node, data))
			return (0);
		del_next(node);
	}
	else if (node->output->type == Redirect_output)
	{
		node->output_fd = open(node->output->args[0], O_WRONLY | O_CREAT \
		| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		del_next(node);
	}
	else if (node->output->type == Redirect_output_append)
	{
		node->output_fd = open(node->output->args[0], O_WRONLY | O_CREAT | \
		O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		del_next(node);
	}
	if (node->output_fd < 0)
		return (0);
	return (1);
}

int	is_builtin(char *str)
{
	int	len;

	if (!str || !ft_isalpha(*str))
		return (0);
	len = ft_strlen(str) + 1;
	if (len > 7 || len < 3)
		return (0);
	if (!ft_strncmp("echo", str, len))
		return (1);
	if (!ft_strncmp("env", str, len))
		return (1);
	if (!ft_strncmp("export", str, len))
		return (1);
	if (!ft_strncmp("exit", str, 5))
		return (1);
	if (!ft_strncmp("pwd", str, len))
		return (1);
	if (!ft_strncmp("cd", str, len))
		return (1);
	if (!ft_strncmp("unset", str, len))
		return (1);
	return (0);
}

int	ft_builtin(t_pnode *node, t_data *data)
{
	int	exit_status;

	exit_status = 0;
	if (!ft_strncmp("echo", node->args[0], 5))
		exit_status = (ft_echo(node->args, node->output_fd));
	else if (!ft_strncmp("env", node->args[0], 4))
		exit_status = (ft_env(data->export_var, node->output_fd));
	else if (!ft_strncmp("export", node->args[0], 7))
		exit_status = (ft_export(node->args, data, node->output_fd));
	else if (!ft_strncmp("exit", node->args[0], 5))
		exit_status = ft_exit(node->args, data);
	else if (!ft_strncmp("pwd", node->args[0], 4))
		return (ft_pwd(node->args, data));
	else if (!ft_strncmp("cd", node->args[0], 3))
		return (ft_cd(node->args, data));
	else if (!ft_strncmp("unset", node->args[0], 6))
		return (ft_unset(node->args, data));
	if (node->output_fd != 1)
		close(node->output_fd);
	return (exit_status);
}

void	handle_input_output_fd(t_pnode *node)
{
	if (node->output_fd != 1)
	{
		dup2(node->output_fd, 1);
		close(node->output_fd);
	}
	if (node->input_fd != 0)
	{
		dup2(node->input_fd, 0);
		close(node->input_fd);
	}
}


int	program_call(t_pnode *node, t_data *data)
{
	pid_t	child_pid;
	int		exit_status;

	if (node->output)
	{
		if (!output_handler(node, data))
		{
			free_tree(node->output);
			node->output = NULL;
			return (1);
		}
	}
	child_pid = ft_fork(&exit_status);
	if (child_pid == -1)
		return (on_return(1, node, node->output_fd, 0));
	else if (child_pid)
		return (on_return(exit_status, NULL, node->output_fd, node->input_fd));
	handle_input_output_fd(node);
	if (is_builtin(node->args[0]))
		ft_exit_pip(ft_builtin(node, data), node, data);
	ft_exec(node, data);
	return (1);
}
