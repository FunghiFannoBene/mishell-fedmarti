/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:35:10 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/24 00:09:30 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "minishell.h"

void	signal_handler(int signo);

void	child_sighandler(int signo)
{
	// printf("receiving signal no. %i\n", signo);
	if (signo == SIGINT)
	{
		// printf("i'm being terminated :0\n");
		exit (130);
	}
}

void	child_logic(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// void	parent_logic(pid_t child_pid, int *exit_status)
// {
// 	signal(SIGINT, SIG_IGN);
// 	if (waitpid(child_pid, exit_status, 0) < 0)
// 	{
// 		*exit_status = 1;
// 		return ;
// 	}
// 	if (WIFEXITED(*exit_status))
// 	{
// 		*exit_status = (WEXITSTATUS(*exit_status));
// 	}
// 	else if (WIFSIGNALED(*exit_status))
// 		*exit_status = WTERMSIG(*exit_status) + 128;
// 	signal(SIGINT, signal_handler);
// }

pid_t	ft_fork(int *exit_status)
{
	pid_t	child_pid;

	child_pid = fork();
	printf("child pid: %i\n", child_pid);
	if (child_pid == 0)
	{
		child_logic();
		return (0);
	}
	else if (child_pid == -1)
	{
		*exit_status = 1;
		return (-1);
	}
	// parent_logic(child_pid, exit_status);
	return (child_pid);
}
