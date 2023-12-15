/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:23:09 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/15 22:57:20 by fedmarti         ###   ########.fr       */
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
		free_tree(node->output);
	return (exit_status);
}

t_pnode	*get_head(t_pnode *node)
{
	while (node->input)
		node = node->input;
	return (node);
}

t_pnode	*get_pcall(t_pnode *node, t_pnode *boundary)
{
	while (node != boundary && node->type != Program_Call)
		node = node->output;
	if (node == boundary)
		return (NULL);
	return (node);
}

void	ft_exit_pip(int exit_status, t_pnode *tree, t_data *data)
{
	free_data(data);
	free_tree(get_head(tree));
	exit(exit_status);
}

void	*free_tree(t_pnode *node)
{
	t_pnode	*prev;

	if (!node)
		return (NULL);
	prev = node->input;
	while (node)
		node = next(node);
	if (prev)
		prev->output = NULL;
	return (NULL);
}
