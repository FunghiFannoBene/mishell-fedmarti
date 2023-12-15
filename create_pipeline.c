/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:47:41 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/15 21:37:21 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "libft/libft.h"

t_pnode	*del_next(t_pnode *node)
{
	t_pnode	*next;

	next = node->output;
	if (!next)
		return (node);
	node->output = next->output;
	if (node->output)
		node->output->input = node;
	next->output = NULL;
	free_node(next);
	return (node);
}

t_pnode	*next(t_pnode *node)
{
	t_pnode	*temp;

	temp = node;
	node = node->output;
	if (node)
	{
		node->input = temp->input;
	}
	if (temp->input)
		temp->output = node;
	temp->output = NULL;
	temp->input = NULL;
	free_node(temp);
	return (node);
}

t_pnode	*node_create(enum e_pnode_type type, char **args, t_pnode *previous)
{
	t_pnode	*new;

	if (type == Null)
		return (NULL);
	new = ft_calloc(sizeof(*new), 1);
	if (!new)
		return (NULL);
	new->pid = 0;
	new->type = type;
	new->args = args;
	new->input = previous;
	new->output = NULL;
	new->input_fd = 0;
	new->output_fd = 1;
	return (new);
}

void	free_node(t_pnode *node)
{
	if (!node)
		return ;
	if (node->args)
		ft_free_matrix((void ***)&node->args, INT_MAX);
	if (node->output)
	{
		node->output->input = NULL;
	}
	free(node);
}
