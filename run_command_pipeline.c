/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:47:08 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/16 16:36:42 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

void	signal_handler(int signo);
t_pnode	*run_command(t_pnode *node, t_data *data, int *exit_status);
int		read_heredocs(t_pnode *node, t_pnode **head, t_data *data);

int	valid_syntax(t_pnode *tree, int *exit_status)
{
	while (tree)
	{
		if (tree->type != Program_Call && tree->type != Pipe)
		{
			if (!tree->args || !*tree->args || !**tree->args)
			{
				*exit_status = syntax_error(tree);
				return (0);
			}
		}
		else if (tree->type == Pipe \
		&& ((!tree->input || tree->input->type == Pipe) \
		|| (!tree->output || tree->output->type == Pipe)))
		{
			*exit_status = syntax_error(tree);
			return (0);
		}
		tree = tree->output;
	}
	return (1);
}

static int	wait_for_children(t_pnode *node, int *exit_status)
{
	while (node)
	{
		if (node->pid > 0)
		{
			if (waitpid(node->pid, exit_status, 0) < 0)
			{
				*exit_status = 1;
				return (1);
			}
			if (WIFEXITED(*exit_status))
				*exit_status = (WEXITSTATUS(*exit_status));
			else if (WIFSIGNALED(*exit_status))
			{
				if (WTERMSIG(*exit_status) == SIGQUIT)
					write (2, "Quit (core dumped)\n", 19);
				*exit_status = WTERMSIG(*exit_status) + 128;
			}
		}
		node = node->output;
	}
	return (*exit_status);
}

int	run_command_pipeline(t_pnode *pipeln_tree, t_data *data)
{
	int		exit_status;
	t_pnode	*head;

	exit_status = 0;
	if (!pipeln_tree)
		return (exit_status);
	if (!valid_syntax(pipeln_tree, &exit_status))
		return (on_return(exit_status, free_tree(pipeln_tree), 1, 0));
	head = pipeln_tree;
	if (read_heredocs(pipeln_tree, &head, data))
		return ((long)free_tree(head) + 1);
	signal(SIGINT, SIG_IGN);
	while (pipeln_tree)
	{
		pipeln_tree = run_command(pipeln_tree, data, &exit_status);
		if (pipeln_tree)
			pipeln_tree = pipeln_tree->output;
	}
	wait_for_children(head, &exit_status);
	signal(SIGINT, signal_handler);
	free_tree(head);
	return (exit_status);
}
