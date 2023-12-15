/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:47:08 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/15 21:36:06 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"


void	signal_handler(int signo);
t_pnode	*run_command(t_pnode *node, t_data *data, int *exit_status);


/*static int	empty_heredoc(t_pnode *node, int *exit_status, t_data *data)
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
}*/

/*static t_pnode	*empty_output(t_pnode *node, t_data *data, int *exit_status)
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
}*/

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
		else if (tree->type == Pipe && (!tree->input || !tree->output))
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

t_pnode	*get_boundary(t_pnode *node);
int		change_fd(int prev_fd, int new_fd, char mode);

t_pnode	*associated_pcall(t_pnode *node, t_pnode *boundary)
{
	while (node != boundary && node->type != Program_Call)
		node = node->output;
	if (node == boundary)
		return (NULL);
	return (node);
}

static void	_child_logic(t_pnode *node, int pipe_fd[2], t_pnode *head, t_data *data)
{
	if (pipe_fd[0])
		close (pipe_fd[0]);
	ft_heredoc(node->args, pipe_fd[1], data);
	close (pipe_fd[1]);
	ft_exit_pip(0, head, data);
}

int	take_input(t_pnode *node, t_data *data, t_pnode *head, t_pnode *prgrm_call)
{
	pid_t	child_pid;
	int		pipe_fd[2];

	pipe_fd[0] = 0;
	if (!prgrm_call)
		pipe_fd[1] = ft_open("/dev/null", O_WRONLY, -1);
	else if (pipe(pipe_fd))
		return (1);
	else
		node->output_fd = pipe_fd[0];
	child_pid = fork();
	if (!child_pid)
		_child_logic(node, pipe_fd, head, data);
	close(pipe_fd[1]);
	if (child_pid == -1)
	{
		if (pipe_fd[0])
			close (pipe_fd[0]);
		return (1);
	}
	waitpid(child_pid, NULL, 0);
	return (0);
}

t_pnode	*node_advance(t_pnode *node, t_pnode *prgrm_call, t_pnode **head)
{
	t_pnode	*output;

	if (!prgrm_call)
	{
		if (node == *head)
			*head = next(node);
		else
		{
			output = node->output;
			node->input->output = next(node);
			node = output;
		}
	}
	else
		node = node->output;
	return (node);
}

void	close_fds(t_pnode *node)
{
	while (node)
	{
		if (node->type == Redirect_input_heredoc && node->output_fd > 1)
			close(node->output_fd);
		node = node->output;
	}
}

int	read_heredocs(t_pnode *node, t_pnode **head, t_data *data)
{
	t_pnode	*boundary;
	t_pnode	*prgrm_call;

	while (node)
	{
		boundary = get_boundary(node);
		prgrm_call = associated_pcall(node, boundary);
		while (node != boundary)
		{
			if (node->type != Redirect_input_heredoc)
			{
				node = node->output;
				continue ;
			}
			if (take_input(node, data, *head, prgrm_call))
			{
				close_fds(*head);
				return (1);
			}
			node = node_advance(node, prgrm_call, head);
		}
		if (node)
			node = node->output;
	}
	return (0);
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
