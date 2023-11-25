/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:21:11 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/25 01:24:41 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

int		redirect_input(t_pnode *node, t_data *data);
int		redirect_input_heredoc(t_pnode *node, t_data *data);
int		program_call(t_pnode *node, t_data *data);

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
	write (2, "minishell: syntax error near unexpected token `|'\n", 51);
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
		exit_status = 0;
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
		exit_status = run_command(node->output->input[1], data);
	return (exit_status);
}
