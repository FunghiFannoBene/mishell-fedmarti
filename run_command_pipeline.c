/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:47:08 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/16 21:32:52 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

int		redirect_input(t_pnode *node, t_data *data);
int		redirect_input_heredoc(t_pnode *node, t_data *data);
int		program_call(t_pnode *node, t_data *data);
void	child_sighandler(int signo);

int	empty_file(t_pnode *node)
{
	int	fd;

	fd = 0;
	if (node->type == Redirect_output)
		fd = open(node->output->args[0], O_WRONLY | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else if (node->type == Redirect_output_append)
		fd = open(node->output->args[0], O_WRONLY | O_CREAT | O_APPEND, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (node->output && !node->output->input[1])
		node->output->input_fd = open("/dev/null", O_RDONLY);
	if (!fd)
		return (1);
	close(fd);
	return (0);
}

int	error_pipe(t_pnode *node)
{
	write (2, "bash: syntax error near unexpected token `|'\n", 46);
	if (node->output && node->output->input[1])
		free_node(node->output->input[1]);
	free_tree(node->output);
	node->output = NULL;
	return (1);
}

int	run_command(t_pnode *node, t_data *data)
{
	int	exit_status;

	if (!node)
		;
	if (node->type == Redirect_input)
		exit_status = redirect_input(node, data);
	else if (node->type == Program_Call)
		exit_status = program_call(node, data);
	else if (node->type == Pipe)
		return (error_pipe(node));
	else if (node->type == Redirect_input_heredoc)
		return (redirect_input_heredoc(node, data));
	else if (node->type == Redirect_output \
	|| node->type == Redirect_output_append)
		return (empty_file(node));
	if (node->output && node->output->input[1] \
	&& node != node->output->input[1])
		run_command(node->output->input[1], data);
	return (0);
}

void	*fork_error(t_pnode *node, int *exit_status)
{
	*exit_status = 1;
	free_tree(node);
	return (NULL);
}

static t_pnode	*preliminary_tests(t_pnode *node, t_data *data, int *exit_status)
{
	pid_t	child_pid;

	if (node && (node->type == Pipe))
	{
		child_pid = ft_fork(exit_status);
		if (child_pid == -1)
			return (fork_error(node, exit_status));
		else if (!child_pid)
			ft_exit(run_command(node, data), node, data);
		free_tree(node);
		return (NULL);
	}
	while (node && (node->type == Redirect_input \
	|| node->type == Redirect_input_heredoc))
	{
		if (node->type == Redirect_input_heredoc)
		{
			child_pid = ft_fork(exit_status);
			if (child_pid == -1)
				return (fork_error(node, exit_status));
			else if (child_pid)
				ft_exit(ft_heredoc(node->args, open("/dev/null", O_WRONLY), \
				data), node, data);
		}
		node = next(node);
	}
	if (node && node->type == Pipe && node->output)
	{
		node = next(node);
		if (node->type == Program_Call)
			node->input_fd = open("/dev/null", O_RDONLY);
	}
	return (node);
}

int	pipeline(t_pnode *node, t_data *data)
{
	int		exit_status;
	t_pnode	*tree_head;

	tree_head = node;
	while (node)
	{
		exit_status = run_command(node, data);
		node = node->output;
	}
	free_tree(tree_head);
	return (exit_status);
}

int	run_command_pipeline(t_pnode *pipeline_tree, t_data *data)
{
	int		exit_status;
	pid_t	child_pid;

	pipeline_tree = preliminary_tests(pipeline_tree, data, &exit_status);
	if (!pipeline_tree)
		return (exit_status);
	pipeline_tree = sort_pipeline_tree(pipeline_tree);
	return (pipeline(pipeline_tree, data));
}
