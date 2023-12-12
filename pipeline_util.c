/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:23:09 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/06 20:10:38 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "minishell.h"

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

t_pnode	*get_head(t_pnode *node)
{
	t_pnode	*temp;

	temp = node;
	while (temp->output)
	{
		if (temp == temp->output->input[1])
		{
			node = temp->output;
			break ;
		}
		temp = temp->output;
	}
	while (node->input[0])
		node = node->input[0];
	return (node);
}

void	ft_exit_pip(int exit_status, t_pnode *tree, t_data *data)
{
	free_data(data);
	free_tree(get_head(tree));
	exit(exit_status);
}

void	free_tree(t_pnode *node)
{
	t_pnode	*temp;
	t_pnode	*prev;

	if (!node)
		return ;
	temp = node;
	while (temp->output)
	{
		if (temp->output->input[1] == temp)
		{
			node = temp->output;
			temp->output = NULL;
			free_tree(get_head(temp));
			node->input[1] = NULL;
		}
		temp = temp->output;
	}
	prev = node->input[0];
	while (node)
		node = next(node);
	if (prev)
		prev->output = NULL;
}
