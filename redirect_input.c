/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:02:19 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/11 00:10:45 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

static int	pipe_and_fork(t_pnode *node, t_data *data)
{
	pid_t	child_pid;
	int		pipe_fd[2];
	int		exit_status;

	if (pipe(pipe_fd))
		ft_exit (1, node, data);
	node->output->input_fd = pipe_fd[0];
	child_pid = fork();
	if (child_pid == -1)
		ft_exit (1, node, data);
	else if (!child_pid)
	{
		close(pipe_fd[0]);
		exit_status = ft_heredoc(node->args, pipe_fd[1], data);
		close(pipe_fd[1]);
		ft_exit(exit_status, node, data);
	}
	return (0);
}

int	redirect_input_heredoc(t_pnode *node, t_data *data)
{
	int		write_fd;

	write_fd = 0;
	if (!node->output || node->output->type == Redirect_input)
	{
		write_fd = open("/dev/null", O_WRONLY);
		if (write_fd == -1)
			return (1);
	}
	if (!node->output)
		return (ft_heredoc(node->args, write_fd, data));
	if (node->output->type == Program_Call)
		pipe_and_fork(node, data);
	return (0);
}

int	redirect_input(t_pnode *node)
{
	if (!node->output)
		return (0);
	node->output->input_fd = open(node->args[0], O_RDONLY);
	if (node->output->input_fd <= 0)
		return (no_such_file_or_directory(node->args[0]));
	return (0);
}
