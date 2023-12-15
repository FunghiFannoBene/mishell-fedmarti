/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:21:11 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/15 22:59:44 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

int		redirect_input(t_pnode *node, int *exit_status);
int		redirect_input_heredoc(t_pnode *node, t_data *data);
int		program_call(t_pnode *node, t_data *data, int pipe_read);
int		redirect_output(t_pnode *node, int *exit_status);
void	ft_exec(t_pnode *node, t_data *data);

static int	output_handler(t_pnode *node, t_pnode *command, \
int write_fd, int *pipe_read_fd)
{
	int		pipe_fd[2];
	t_pnode	*boundary;
	t_pnode	*next_command;

	boundary = get_boundary(node);
	next_command = get_pcall(node, boundary);
	if (!next_command)
		return (write_fd);
	if (write_fd == 1 && command)
	{
		if (pipe(pipe_fd))
			return (-1);
		write_fd = change_fd(write_fd, pipe_fd[1], 'w');
		*pipe_read_fd = pipe_fd[0];
		next_command->input_fd = \
		change_fd(next_command->input_fd, pipe_fd[0], 'r');
	}
	else
		next_command->input_fd = change_fd(next_command->input_fd, \
		ft_open("/dev/null", O_RDONLY, -1), 'r');
	return (write_fd);
}

static t_pnode	*check_fd_error(t_pnode *node, int fd[2], \
t_pnode *boundary, t_pnode **command)
{
	if (fd[0] >= 0 && fd[1] >= 0)
		return (node);
	change_fd(fd[0], 0, 'r');
	change_fd(fd[1], -1, 'w');
	while (node != boundary)
	{
		if (node->type == Redirect_input_heredoc && node->output_fd > 1)
			close(node->output_fd);
		node = node->output;
	}
	if (*command)
	{
		*command = NULL;
	}
	return (node);
}

static int	swap_fds(int fd[2], t_pnode *node, int *exit_status)
{
	if (node->type == Redirect_input)
		fd[0] = change_fd(fd[0], redirect_input(node, exit_status), 'r');
	else if (node->type == Redirect_input_heredoc)
		fd[0] = change_fd(fd[0], node->output_fd, 'r');
	else if (node->type == Redirect_output \
	|| node->type == Redirect_output_append)
		fd[1] = change_fd(fd[1], redirect_output(node, exit_status), 'w');
	return (fd[0] < 0 || fd[1] < 0);
}

static int	_vars_init(t_pnode **command, \
t_pnode **boundary, int fd[2], t_pnode **node)
{
	*boundary = get_boundary(*node);
	*command = get_pcall(*node, *boundary);
	if (*command)
	{
		fd[0] = (*command)->input_fd;
		fd[1] = (*command)->output_fd;
		if ((*command)->args == NULL || (*command)->args[0] == NULL \
		|| (*command)->args[0][0] == '\0')
			*command = NULL;
	}
	else
	{
		fd[0] = 0;
		fd[1] = 1;
	}
	return (0);
}

t_pnode	*run_command(t_pnode *node, t_data *data, int *exit_status)
{
	int		pipe_read;
	t_pnode	*command;
	t_pnode	*boundary;
	int		fd[2];

	pipe_read = _vars_init(&command, &boundary, fd, &node);
	while (node != boundary)
	{
		if (node->type != Program_Call && swap_fds(fd, node, exit_status))
			break ;
		node = node->output;
	}
	node = check_fd_error(node, fd, boundary, &command);
	if (boundary)
	{
		fd[1] = output_handler(boundary->output, command, fd[1], &pipe_read);
		if (fd[1] < 0 && on_return(1, boundary, 1, fd[0]))
			return ((void *)((long)(*exit_status = 1) *0));
	}
	if (!command)
		return (on_return(0, NULL, fd[1], fd[0]) + node);
	command->input_fd = fd[0];
	command->output_fd = fd[1];
	*exit_status = program_call(command, data, pipe_read);
	return (node);
}
