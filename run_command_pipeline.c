/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:47:08 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/13 00:47:26 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

int		is_builtin(char *str);
int		ft_builtin(t_pnode *node, t_data *data);
void	signal_handler(int signo);
int		run_command(t_pnode *node, t_data *data);
int		single_builtin(t_pnode *node, t_data *data);

static int	empty_heredoc(t_pnode *node, int *exit_status, t_data *data)
{
	int	fd;

	if (node->type != Redirect_input_heredoc)
		return (1);
	node->pid = ft_fork(exit_status);
	if (node->pid == -1)
	{
		*exit_status = 1;
		return (1);
	}
	else if (!node->pid)
	{
		fd = open("/dev/null", O_WRONLY);
		if (fd < 0)
			ft_exit_pip(1, node, data);
		ft_exit_pip(ft_heredoc(node->args, fd, data), node, data);
	}
	waitpid(node->pid, exit_status, 0);
	*exit_status = WEXITSTATUS(*exit_status);
	return (*exit_status);
}

static t_pnode	*empty_output(t_pnode *node, t_data *data, int *exit_status)
{
	int	fd;

	while (is_type(node, (t_ntype[]){4, 3, 0}))
	{
		if (node->type == 4 && empty_heredoc(node, exit_status, data))
		{
			free_tree(node);
			return (NULL);
		}
		else if (node->type == Redirect_input)
		{
			fd = ft_open(node->args[0], O_RDONLY, -1);
			if (fd >= 0)
				close (fd);
			*exit_status = (fd < 0);
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
		else if (tree->type == Pipe && (!tree->input[0] || !tree->output))
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
	if (pipeln_tree->output == NULL \
	&& pipeln_tree->args && is_builtin(pipeln_tree->args[0]))
		return (single_builtin(pipeln_tree, data));
	if (!valid_syntax(pipeln_tree, &exit_status))
		return (on_return(exit_status, free_tree(pipeln_tree), 1, 0));
	pipeln_tree = empty_output(pipeln_tree, data, &exit_status);
	if (!pipeln_tree)
		return (exit_status);
	signal(SIGINT, SIG_IGN);
	pipeln_tree = sort_pipeline_tree(pipeln_tree);
	head = pipeln_tree;
	while (pipeln_tree)
	{
		exit_status = run_command(pipeln_tree, data);
		pipeln_tree = pipeln_tree->output;
	}
	wait_for_children(head, &exit_status);
	signal(SIGINT, signal_handler);
	free_tree(head);
	return (exit_status);
}
