/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:35:10 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/25 01:29:12 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "minishell.h"

void	signal_handler(int signo);

pid_t	ft_fork(int *exit_status)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		return (0);
	}
	else if (child_pid)
		return (child_pid);
	*exit_status = 1;
	return (-1);
}
