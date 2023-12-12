/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:02:19 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/13 00:18:54 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

static int	child_logic(t_pnode *node, t_data *data, int read_fd)
{
	int	exit_status;

	if (read_fd)
		close(read_fd);
	exit_status = ft_heredoc(node->args, node->output_fd, data);
	close(node->output_fd);
	ft_exit_pip(exit_status, node, data);
	return (1);
}

static int	parent_logic(t_pnode *node)
{
	int	exit_status;

	waitpid(node->pid, &exit_status, 0);
	node->pid = 0;
	return (on_return(WEXITSTATUS(exit_status), NULL, 1, node->output_fd));
}

int	redirect_input_heredoc(t_pnode *node, t_data *data)
{
	int		pipe_fd[2];
	int		exit_status;

	exit_status = 0;
	ft_bzero(pipe_fd, sizeof(pipe_fd));
	if (!node->output || node->output->type != Program_Call)
		node->output_fd = open("/dev/null", O_WRONLY);
	else
	{
		exit_status = pipe(pipe_fd);
		node->output->input_fd = pipe_fd[0];
		node->output_fd = pipe_fd[1];
	}
	if (node->output_fd < 0 || exit_status)
		return (on_return(1, node, 1, 0));
	node->pid = ft_fork(&exit_status);
	if (node->pid == -1)
		return (on_return(exit_status, node, \
		node->output->input_fd, node->output_fd));
	else if (node->pid)
		return (parent_logic(node));
	return (child_logic(node, data, pipe_fd[0]));
}

int	redirect_input(t_pnode *node)
{
	if (node->input_fd)
		close(node->input_fd);
	node->output->input_fd = ft_open(node->args[0], O_RDONLY, -1);
	if (node->output->input_fd <= 0)
	{
		free_tree(node->output);
		return (1);
	}
	return (0);
}
