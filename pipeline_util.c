/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:23:09 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/12 01:21:09 by fedmarti         ###   ########.fr       */
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

pid_t	ft_fork(void)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid)
	{
		waitpid(child_pid, NULL, 0);
		return (child_pid);
	}
	signal(SIGINT, child_sighandler);
	return (0);
}

void	ft_exit(int exit_status, t_pnode *tree, t_data *data)
{
	free_data(data);
	free_tree(tree);
	exit(exit_status);
}
