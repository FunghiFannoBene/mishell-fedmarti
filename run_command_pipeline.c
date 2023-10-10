/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:47:08 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/11 01:13:28 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

int	redirect_input(t_pnode *node, t_data *data);
int	redirect_input_heredoc(t_pnode *node, t_data *data);

int	run_command(t_pnode *node, t_data *data)
{
	if (!node)
		return (0);
	if (node->type == Redirect_input)
		return (redirect_input(node, data));
	else if (node->type == Program_Call)
		return (program_call(node, data));
	else if (node->type == Pipe)
	{
		write (2, "bash: syntax error near unexpected token `|'\n", 46);
		ft_exit(2, node, data);
	}
	else if (node->type == Redirect_input_heredoc)
		return (redirect_input_heredoc(node, data));
	else if (node->type == Redirect_output \
	|| node->type == Redirect_output_append)
		return (redirect_output(node, data));
	return (0);
}

void	pipeline(t_pnode *node, t_data *data)
{
	if (node && (node->type == Pipe))
		return (run_command(node, data));
	while (node && (node->type == Redirect_input \
	|| node->type == Redirect_input_heredoc))
	{
		if (node->type == Redirect_input_heredoc)
			ft_heredoc(node->args, open("/dev/null", O_WRONLY), data);
		node = next(node);
	}
	if (!node)
		return ;
	if (node->type == Pipe && node->output)
	{
		node = next(node);
		if (node->type == Program_Call)
			node->input_fd = open("/dev/null", O_RDONLY);
	}
	node = sort_pipeline_tree(node);
	while (node)
	{
		run_command(node, data);
		node = next(node);
	}
}

int	run_command_pipeline(t_pnode *pipeline_tree, t_data *data)
{
	int		exit_status;
	pid_t	child_pid;

	child_pid = ft_fork();
	if (child_pid == -1)
	{
		free_tree(pipeline_tree);
		return (1);
	}
	else if (child_pid)
		waitpid(child_pid, &exit_status, 0);
	else
	{
		pipeline(pipeline_tree, data);
		ft_exit(0, NULL, data);
	}
	return (exit_status);
}
