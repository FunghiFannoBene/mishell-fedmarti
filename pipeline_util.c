/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:23:09 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/11 01:18:54 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "minishell.h"

static void	child_sighandler(int signo)
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
		return (child_pid);
	signal(SIGINT, child_sighandler);
}

void	ft_exit(int exit_status, t_pnode *tree, t_data *data)
{
	free_data(data);
	free_tree(tree);
	exit(exit_status);
}
