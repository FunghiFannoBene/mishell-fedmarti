/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_pipeline_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:03:32 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/07 23:56:06 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

enum e_swap_mode {
	No_swap,
	Input1,
	Input2,
};

int	is_type(t_pnode *node, t_ntype *types)
{
	int	i;

	i = 0;
	while (types[i] != Null)
	{
		if (node->type == types[i])
			return (1);
		i++;
	}
	return (0);
}

static t_pnode	*node_swap(t_pnode *node, enum e_swap_mode mode)
{
	t_pnode	*next;

	next = node->output;
	if (mode == Input1)
	{
		node->input[1] = node->input[0];
		node->input[0] = next;
		node->output = next->output;
		next->output = node;
		next->input[0] = node->input[1];
		node->input[1] = NULL;
		return (next);
	}
	else if (mode == Input2)
	{
		node->input[1] = next;
		node->output = next->output;
		next->output = node;
		next->input[0] = NULL;
		return (node);
	}
	return (node);
}

static enum e_swap_mode	get_swap_type(t_pnode *node)
{
	if (node->type != Program_Call)
		return (No_swap);
	if (!is_type(node->output, \
	(t_ntype[]){Redirect_input, Redirect_input_heredoc, Null}))
		return (No_swap);
	if (node->input[0])
		return (Input2);
	return (Input1);
}

t_pnode	*sort_pipeline_tree(t_pnode *input_tree)
{
	t_pnode				*current;
	t_pnode				*head;

	if (!input_tree || !input_tree->output)
		return (input_tree);
	head = node_swap(input_tree, get_swap_type(input_tree));
	current = head->output;
	while (current)
	{
		current = node_swap(current, get_swap_type(current));
		current = current->output;
	}
	return (head);
}
