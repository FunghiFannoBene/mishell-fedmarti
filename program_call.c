/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:39:11 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/09 02:52:58 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "minishell.h"

static int	pipe_next(t_pnode *node, int *exit_status)
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
		return ((int)run_command(next(node), data, exit_status));
	if (pipe(pipe_fd))
		return (0);
	node->output_fd = pipe_fd[1];
	next_next->input_fd = pipe_fd[0];
	node->output = next(node->output);
	return (1);
}

pid_t	program_Call(t_pnode *node, t_data *data, int *exit_status)
{
	pid_t	child_pid;
	char	**env;
	
	if (!node->output)
		;
	else if (node->output->type == Pipe)
	{
		if (!pipe_next(node, exit_status))
			return (0);
	}
	else if (node->output->type == Redirect_output)
		node->output_fd = open(node->output->args[0], O_WRONLY | O_CREAT, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else if (node->output->type == Redirect_output_append)
		node->output_fd = open(node->output->args[0], O_WRONLY | O_CREAT | \
		O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	child_pid = ft_fork();
	if (child_pid)
		return (child_pid);
	env = env_list_to_array(data->export_var);
	if (!env)
		ft_exit(1, node, data);
	if (node->output_fd != 1)
		dup2(node->output_fd, 1);
	if (node->input_fd != 0)
		dup2(node->input_fd, 0);
	
}
