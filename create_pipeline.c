/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:47:41 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/16 20:26:30 by fedmarti         ###   ########.fr       */
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
		node->output->input[0] = node;
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
		node->input[0] = temp->input[0];
		if (node->input[1] != temp)
			free(node->input[1]);
	}
	free_node(temp);
	return (node);
}

t_pnode	*node_create(enum e_pnode_type type, char **args, t_pnode *previous)
{
	t_pnode	*new;

	if (type == Null)
		return (NULL);
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->type = type;
	new->args = args;
	new->input[0] = previous;
	new->input[1] = NULL;
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
		if (node == node->output->input[0])
			node->output->input[0] = NULL;
		else
			node->output->input[1] = NULL;
	}
	free(node);
}

void	free_tree(t_pnode *head)
{
	t_pnode	*node;

	head = next(head);
	while (head)
	{
		node = head->output;
		if (node && node->input[1])
			free_node(node->input[1]);
		free_node(head);
		head = node;
	}
}
