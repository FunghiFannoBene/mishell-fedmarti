/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:21:11 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/06 18:22:31 by fedmarti         ###   ########.fr       */
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
	if (!node->args || !*node->args || !**node->args)
		return (syntax_error(node));
	if (node->type == Redirect_output)
	{
		fd = ft_open(node->args[0], O_WRONLY | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		write(1, "", 1);
	}
	else if (node->type == Redirect_output_append)
		fd = ft_open(node->args[0], O_WRONLY | O_CREAT | O_APPEND, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (node->output && !node->output->input[1])
		node->output->input_fd = open("/dev/null", O_RDONLY);
	if (!fd || fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	syntax_error(t_pnode *node)
{
	if (node->type == Pipe || (node->output && node->output->type == Pipe))
		write (2, "minishell: syntax error near unexpected token `|'\n", 50);
	else
		write(2, \
		"minishell: syntax error near unexpected token `newline'\n", 56);
	return (2);
}

int	single_builtin(t_pnode *node, t_data *data)
{
	int	exit_status;

	exit_status = ft_builtin(node, data);
	free_node(node);
	return (exit_status);
}

int	run_command(t_pnode *node, t_data *data)
{
	int	exit_status;

	if (!node)
		exit_status = 0;
	if (!node->args || !*node->args || *node->args == 0)
		return (syntax_error(node));
	if (node->type == Redirect_input)
		exit_status = redirect_input(node, data);
	else if (node->type == Program_Call)
		exit_status = program_call(node, data);
	else if (node->type == Pipe)
		return (syntax_error(node));
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
