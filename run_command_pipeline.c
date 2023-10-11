/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:47:08 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/11 21:31:51 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

int		redirect_input(t_pnode *node, t_data *data);
int		redirect_input_heredoc(t_pnode *node, t_data *data);
void	program_call(t_pnode *node, t_data *data);

int	run_command(t_pnode *node, t_data *data)
{	
	if (!node)
		;
	if (node->type == Redirect_input)
		redirect_input(node, data);
	else if (node->type == Program_Call)
		program_call(node, data);
	else if (node->type == Pipe)
	{
		write (2, "bash: syntax error near unexpected token `|'\n", 46);
		ft_exit(2, node, data);
	}
	else if (node->type == Redirect_input_heredoc)
		redirect_input_heredoc(node, data);
	else if (node->type == Redirect_output \
	|| node->type == Redirect_output_append)
		;
	return (0);
}

static t_pnode *preliminary_tests(t_pnode *node, t_data *data, int *exit_status)
{
	if (node && (node->type == Pipe))
	{
		run_command(node, data);
		return (NULL);
	}
	while (node && (node->type == Redirect_input \
	|| node->type == Redirect_input_heredoc))
	{
		if (node->type == Redirect_input_heredoc)
			ft_heredoc(node->args, open("/dev/null", O_WRONLY), data);
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
	int	exit_status;
	
	node = preliminary_tests(node, data, &exit_status);
	if (!node)
		return (exit_status);
	node = sort_pipeline_tree(node);
	while (node)
	{
		exit_status = run_command(node, data);
		node = next(node);
	}
	return (exit_status);
}

int	run_command_pipeline(t_pnode *pipeline_tree, t_data *data)
{
	int		exit_status;
	pid_t	child_pid;

	child_pid = ft_fork();
	if (!child_pid)
	{
		sleep(20);
		exit_status = pipeline(pipeline_tree, data);
		ft_exit(exit_status, NULL, data);
	}
	else
	{
		free_tree(pipeline_tree);
		if (child_pid == -1)
			return (1);
		waitpid(child_pid, &exit_status, 0);
	}
	return (exit_status);
}
