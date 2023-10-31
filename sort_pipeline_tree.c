/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_pipeline_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:03:32 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/09 17:18:10 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

enum e_swap_mode {
	No_swap,
	Input0,
	Input1
};

static inline t_pnode	*last_redirect_input(t_pnode *node)
{
	while (is_type(node->output, \
	(t_ntype[]){Redirect_input, Redirect_input_heredoc, Null}))
		node = node->output;
	return (node);
}

int	is_type(t_pnode *node, t_ntype *types)
{
	int	i;

	i = 0;
	if (!node)
		return (0);
	while (types[i] != Null)
	{
		if (node->type == types[i])
			return (1);
		i++;
	}
	return (0);
}

t_pnode	*node_swap(t_pnode *node, t_pnode *last_redirect_input, \
enum e_swap_mode swap_mode)
{
	t_pnode	*next_n;

	next_n = node->output;
	if (swap_mode == Input0)
	{
		next_n = node->output;
		node->input[1] = node->input[0];
		node->input[0] = last_redirect_input;
		node->output = last_redirect_input->output;
		last_redirect_input->output = node;
		next_n->input[0] = node->input[1];
		node->input[1] = NULL;
		return (next_n);
	}
	else if (swap_mode == Input1)
	{
		next_n = node->output;
		node->input[1] = last_redirect_input;
		node->output = last_redirect_input->output;
		last_redirect_input->output = node;
		next_n->input[0] = NULL;
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
		return (Input1);
	return (Input0);
}

t_pnode	*sort_pipeline_tree(t_pnode *input_tree)
{
	t_pnode				*current;
	t_pnode				*head;
	enum e_swap_mode	swap_type;

	if (!input_tree || !input_tree->output)
		return (input_tree);
	swap_type = get_swap_type(input_tree);
	head = node_swap(input_tree, last_redirect_input(input_tree), swap_type);
	current = head->output;
	while (current)
	{
		swap_type = get_swap_type(current);
		if (swap_type != No_swap)
			current = \
			node_swap(current, last_redirect_input(current), swap_type);
		current = current->output;
	}
	return (head);
}
