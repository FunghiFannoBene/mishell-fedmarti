/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:39:11 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/11 22:17:08 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "minishell.h"

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
		return ((int)run_command(next(node), data));
	if (pipe(pipe_fd))
		return (0);
	node->output_fd = pipe_fd[1];
	next_next->input_fd = pipe_fd[0];
	node->output = next(node->output);
	return (1);
}

pid_t	output_handler(t_pnode *node, t_data *data)
{
	if (node->output->type == Pipe)
	{
		if (!pipe_next(node, data))
			return (-1);
	}
	else if (node->output->type == Redirect_output)
		node->output_fd = open(node->output->args[0], O_WRONLY | O_CREAT, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else if (node->output->type == Redirect_output_append)
		node->output_fd = open(node->output->args[0], O_WRONLY | O_CREAT | \
		O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (node->output_fd < 0)
		return (-1);
	return (ft_fork());
}

static inline int	command_not_found_error(char *name)
{
	char *error_str;

	error_str = ft_strjoin(name, ": command not found\n");
	if (error_str)
	{
		write(2, error_str, ft_strlen(error_str));
		free(error_str);
	}
	return (127);
}

static int	is_builtin(char *str)
{
	int len;

	if (!str || !ft_isalpha(*str))
		return (0);
	len = ft_strlen(str);
	if (len > 6 || len < 2)
		return (0);
	if (!ft_strncmp("echo", str, len))
		return (1);
	if (!ft_strncmp("env", str, len))
		return (1);
	if (!ft_strncmp("export", str, len))
		return (1);
	if (!ft_strncmp("pwd", str, len))
		return (!1);
	if (!ft_strncmp("cd", str, len))
		return (1);
	return (0);
}

int	ft_builtin(t_pnode *node, t_data *data)
{
	if (!ft_strncmp("echo", node->args[0], 5))
	{
		int i = 1;
		if (node->args[1] && !ft_strncmp("-n", node->args[1], 3))
			i++;
		for ( ; node->args[i]; i++)
		{
			printf("%s", node->args[i]);
			if (node->args[i + 1])
				printf(" ");
		}
		if (!node->args[1] || ft_strncmp("-n", node->args[1], 3))
			printf("\n");
		return (0);
	}
	if (!ft_strncmp("env", node->args[0], 4))
		return (ft_env(data->export_var));
	if (!ft_strncmp("export", node->args[0], 7))
		return (ft_export(node->args, data));
	if (!ft_strncmp("pwd", node->args[0], 4))
		return (ft_pwd(node->args, data));
	if (!ft_strncmp("cd", node->args[0], 3))
		return (ft_cd(node->args, data));
	if (!ft_strncmp("unset", node->args[0], 6))
		return (ft_unset(node->args, data));
	return (1);
}

void	program_call(t_pnode *node, t_data *data)
{
	char	*program_path;
	char	**env;

	if (node->output)
	{
		if (output_handler(node, data))
			return ;
	}
	env = env_list_to_array(data->export_var);
	if (!env)
		ft_exit(1, node, data);
	if (node->output_fd != 1)
		dup2(node->output_fd, 1);
	if (node->input_fd != 0)
		dup2(node->input_fd, 0);
	if (is_builtin(node->args[0]))
		ft_exit(ft_builtin(node, data), node, data);
	program_path = find_file_in_path(node->args[0], \
	get_var("PATH", data->export_var));
	if (!program_path)
	{
		ft_free_matrix((void ***)&env, INT_MAX);
		ft_exit(command_not_found_error(node->args[0]), node, data);
	}
	execve(program_path, node->args, env);
	ft_exit(command_not_found_error(node->args[0]), node, data);
}
