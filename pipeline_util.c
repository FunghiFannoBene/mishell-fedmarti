/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:23:09 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/15 23:53:49 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "minishell.h"

void	child_sighandler(int signo)
{
	// printf("receiving signal no. %i\n", signo);
	if (signo == SIGINT)
	{
		// printf("i'm being terminated :0\n");
		exit (130);
	}
}

void	free_data(t_data *data);

//closes fd1 if != 1 and fd2 if > 0
//if non-NULL frees the whole tree excluding node (starts from node->output)
//returns exit_status
int	on_return(int exit_status, t_pnode *node, int fd1, int fd2)
{
	if (fd1 != 1)
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
	if (child_pid == 0)
	{
		signal(SIGINT, child_sighandler);
		return (0);
	}
	else if (child_pid == -1)
	{
		*exit_status = 1;
		return (-1);
	}
	if (waitpid(child_pid, exit_status, 0) < 0)
	{
		*exit_status = 1;
		return (-1);
	}
	if (WIFEXITED(*exit_status))
		*exit_status = (WEXITSTATUS(*exit_status));
	else if (WIFSIGNALED(*exit_status))
		*exit_status = 137;
	else if (WIFSTOPPED(*exit_status))
		*exit_status = 130;
	return (child_pid);
}

// pid_t	ft_fork(int *exit_status)
// {
// 	pid_t	child_pid;

// 	child_pid = fork();
// 	if (child_pid == 0)
// 	{
// 		signal(SIGINT, child_sighandler);
// 		return (0);
// 	}
// 	else if (child_pid == -1)
// 	{
// 		*exit_status = 1;
// 		return (-1);
// 	}
// 	if (waitpid(child_pid, exit_status, 0) < 0)
// 	{
// 		*exit_status = 1;
// 		return (-1);
// 	}
// 	if (WIFEXITED(*exit_status)) {
// 		printf("exited, status=%d\n", WEXITSTATUS(*exit_status));
// 	} else if (WIFSIGNALED(*exit_status)) {
// 		printf("killed by signal %d\n", WTERMSIG(*exit_status));
// 	} else if (WIFSTOPPED(*exit_status)) {
// 		printf("stopped by signal %d\n", WSTOPSIG(*exit_status));
// 	} else if (WIFCONTINUED(*exit_status)) {
// 		printf("continued\n");
// 	}
// 	return (child_pid);
// }


void	ft_exit_pip(int exit_status, t_pnode *tree, t_data *data)
{
	free_data(data);
	free_tree(tree);
	exit(exit_status);
}
