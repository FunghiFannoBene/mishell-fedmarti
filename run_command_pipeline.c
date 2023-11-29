/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:47:08 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/25 18:53:01 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

int		is_builtin(char *str);
int		ft_builtin(t_pnode *node, t_data *data);
void	signal_handler(int signo);
int		run_command(t_pnode *node, t_data *data);
int		single_builtin(t_pnode *node, t_data *data);

static t_pnode	*empty_heredoc(t_pnode *node, int *exit_status, t_data *data)
{
	if (node->type != Redirect_input_heredoc)
		return (next(node));
	node->pid = ft_fork(exit_status);
	if (node->pid == -1)
	{
		*exit_status = 1;
		free_tree(node);
		return (NULL);
	}
	else if (!node->pid)
		ft_exit_pip(ft_heredoc(node->args, open("/dev/null", O_WRONLY), \
		data), node, data);
	waitpid(node->pid, exit_status, 0);
	return (next(node));
}

static t_pnode	*format_checks(t_pnode *node, t_data *data, int *exit_status)
{
	if (node && (node->type == Pipe))
	{
		node->pid = ft_fork(exit_status);
		if (node->pid == -1)
		{
			*exit_status = 1;
			free_tree(node);
			return (NULL);
		}
		else if (!node->pid)
			ft_exit_pip(run_command(node, data), node, data);
		waitpid(node->pid, exit_status, 0);
		free_tree(node);
		return (NULL);
	}
	while (node && (node->type == Redirect_input \
	|| node->type == Redirect_input_heredoc))
		node = empty_heredoc(node, exit_status, data);
	if (node && node->type == Pipe && node->output)
	{
		node = next(node);
		if (node->type == Program_Call)
			node->input_fd = open("/dev/null", O_RDONLY);
	}
	return (node);
}

static void	sa_quit(int signo)
{
	if (signo == SIGQUIT)
		write (2, "Quit (core dumped)\n", 20);
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
				*exit_status = WTERMSIG(*exit_status) + 128;
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
	if (pipeln_tree->output == NULL && is_builtin(pipeln_tree->args[0]))
		return (single_builtin(pipeln_tree, data));
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, sa_quit);
	pipeln_tree = format_checks(pipeln_tree, data, &exit_status);
	if (!pipeln_tree)
		return (exit_status);
	pipeln_tree = sort_pipeline_tree(pipeln_tree);
	head = pipeln_tree;
	while (pipeln_tree)
	{
		exit_status = run_command(pipeln_tree, data);
		pipeln_tree = pipeln_tree->output;
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	wait_for_children(head, &exit_status);
	free_tree(head);
	return (exit_status);
}
