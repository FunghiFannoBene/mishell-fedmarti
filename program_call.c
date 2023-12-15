/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:39:11 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/15 02:14:34 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "minishell.h"

void	ft_exec(t_pnode *node, t_data *data);

//creates pipe or opens /dev/null and sets the nodes' input/output fd's
//returns 1 on success, 0 on failure
/*static int	pipe_next(t_pnode *node, t_data *data)
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
}*/

int	redirect_output(t_pnode *node, int *exit_status)
{
	int	fd;

	if (!node->args || !*node->args || !**node->args)
		return (syntax_error(node->output));
	if (node->type == Redirect_output)
		fd = ft_open(node->args[0], OVERWRITE_FLAGS, AUTH_FLAGS);
	else
		fd = ft_open(node->args[0], APPEND_FLAGS, AUTH_FLAGS);
	if (fd < 0)
		*exit_status = 1;
	return (fd);
}
/*
//creates pipes or opens files if needed and sets the node's output fd
//returns 1 on success and 0 on failure
int	output_handler(t_pnode *node, t_data *data, int *exit_status)
{
	if (node->output && node->output->type == Pipe)
	{
		if (!pipe_next(node, data))
		{
			*exit_status = 1;
			return (0);
		}
		del_next(node);
	}
	else if 
	(!node->output->args || !*node->output->args || !**node->output->args)
	{
		*exit_status = syntax_error(node->output);
		return (0);
	}
	else if (node->output->type == Redirect_output 
	|| node->output->type == Redirect_output_append)
	{
		if (redirect_output(node, exit_status))
			return (1);
		return (0);
	}
	if (node->output_fd < 0)
		*exit_status = 1;
	return (node->output_fd >= 0);
}*/

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

int	program_call(t_pnode *node, t_data *data, int pipe_read)
{
	int		exit_status;

	exit_status = 0;
	node->pid = ft_fork(&exit_status);
	if (node->pid > 0)
		return (on_return(exit_status, NULL, node->output_fd, node->input_fd));
	if (pipe_read)
		close(pipe_read);
	if (node->pid == -1)
		return (on_return(-1, node, node->output_fd, node->input_fd));
	if (is_builtin(node->args[0]))
		ft_exit_pip(ft_builtin(node, data), node, data);
	handle_input_output_fd(node);
	ft_exec(node, data);
	return (1);
}
