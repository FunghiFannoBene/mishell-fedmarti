/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:23:09 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/13 01:03:40 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "minishell.h"

void	child_sighandler(int signo)
{
	if (signo == SIGINT)
		exit (130);
}

void	free_data(t_data *data);

//closes fd1 and fd2 if > 0
//if non-NULL frees the whole tree excluding node (starts from node->output)
//returns exit_status
int	on_return(int exit_status, t_pnode *node, int fd1, int fd2)
{
	if (fd1 > 0)
		close(fd1);
	if (fd2 > 0)
		close(fd2);
	if (node)
	{
		if (node->output && node->output->input[1])
			free(node->output->input[1]);
		free_tree(node->output);
		node->output = NULL;
	}
	return (exit_status);
}

pid_t	ft_fork(int *exit_status)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid > 0)
	{
		waitpid(child_pid, exit_status, 0);
		return (child_pid);
	}
	else if (child_pid == -1)
	{
		*exit_status = 1;
		return (-1);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, child_sighandler);
	return (0);
}

void	ft_exit(int exit_status, t_pnode *tree, t_data *data)
{
	free_data(data);
	free_tree(tree);
	exit(exit_status);
}
