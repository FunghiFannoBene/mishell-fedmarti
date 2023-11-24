/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:02:19 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/24 00:23:58 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

int	redirect_input_heredoc(t_pnode *node, t_data *data)
{
	int		pipe_fd[2];
	int		exit_status;

	if (!node->output || node->output->type != Program_Call)
	{
		node->output_fd = open("/dev/null", O_WRONLY);
		if (node->output_fd == -1)
			return (1);
		return (ft_heredoc(node->args, node->output_fd, data));
	}
	if (pipe(pipe_fd))
		return (on_return(1, node, 0, 0));
	node->output->input_fd = pipe_fd[0];
	node->pid = ft_fork(&exit_status);
	if (node->pid == -1)
		return (on_return(exit_status, node, pipe_fd[0], pipe_fd[1]));
	else if (node->pid)
		return (on_return(exit_status, NULL, 1, pipe_fd[1]));
	close(pipe_fd[0]);
	exit_status = ft_heredoc(node->args, pipe_fd[1], data);
	close(pipe_fd[1]);
	ft_exit_pip(exit_status, node, data);
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
