/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:46:16 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/15 23:00:34 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "minishell.h"

static void	_child_logic(t_pnode *node, int pipe_fd[2], \
t_pnode *head, t_data *data)
{
	if (pipe_fd[0])
		close (pipe_fd[0]);
	ft_heredoc(node->args, pipe_fd[1], data);
	close (pipe_fd[1]);
	ft_exit_pip(0, head, data);
}

int	take_input(t_pnode *node, t_data *data, t_pnode *head, t_pnode *prgrm_call)
{
	pid_t	child_pid;
	int		pipe_fd[2];

	pipe_fd[0] = 0;
	if (!prgrm_call)
		pipe_fd[1] = ft_open("/dev/null", O_WRONLY, -1);
	else if (pipe(pipe_fd))
		return (1);
	else
		node->output_fd = pipe_fd[0];
	child_pid = fork();
	if (!child_pid)
		_child_logic(node, pipe_fd, head, data);
	close(pipe_fd[1]);
	if (child_pid == -1)
	{
		if (pipe_fd[0])
			close (pipe_fd[0]);
		return (1);
	}
	waitpid(child_pid, NULL, 0);
	return (0);
}

t_pnode	*node_advance(t_pnode *node, t_pnode *prgrm_call, t_pnode **head)
{
	t_pnode	*output;

	if (!prgrm_call)
	{
		if (node == *head)
			*head = next(node);
		else
		{
			output = node->output;
			node->input->output = next(node);
			node = output;
		}
	}
	else
		node = node->output;
	return (node);
}

void	close_fds(t_pnode *node)
{
	while (node)
	{
		if (node->type == Redirect_input_heredoc && node->output_fd > 1)
			close(node->output_fd);
		node = node->output;
	}
}

int	read_heredocs(t_pnode *node, t_pnode **head, t_data *data)
{
	t_pnode	*boundary;
	t_pnode	*prgrm_call;

	while (node)
	{
		boundary = get_boundary(node);
		prgrm_call = get_pcall(node, boundary);
		while (node != boundary)
		{
			if (node->type != Redirect_input_heredoc)
			{
				node = node->output;
				continue ;
			}
			if (take_input(node, data, *head, prgrm_call))
			{
				close_fds(*head);
				return (1);
			}
			node = node_advance(node, prgrm_call, head);
		}
		if (node)
			node = node->output;
	}
	return (0);
}
