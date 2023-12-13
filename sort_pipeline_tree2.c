/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_pipeline_tree2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:19:30 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/13 01:29:53 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

// static inline t_pnode	*last_redirect_input(t_pnode *node)
// {
// 	while (is_type(node->output, 
// 	(t_ntype[]){Redirect_input, Redirect_input_heredoc, Null}))
// 		node = node->output;
// 	return (node);
// }

static void	shift_back(t_pnode *node, t_pnode *last_pcall)
{
	t_pnode	*prev;
	t_pnode	*next;

	prev = last_pcall;
	while (is_type(prev->output, \
	(t_ntype[]){Redirect_input, Redirect_input_heredoc, Null}) \
	&& prev->output != node)
	{
		prev = prev->output;
	}
	next = prev->output;
	if (node == next)
		return ;
	node->input[0]->output = node->output;
	prev->output = node;
	node->input[0] = prev;
	if (next)
		next->input[0] = node;
	node->output = next;
}

t_pnode	*shift_redirect_output(t_pnode *node)
{
	t_pnode	*last_pcall;
	t_pnode	*head;

	head = node;
	while (node)
	{
		if (node->type == Program_Call)
			last_pcall = node;
		else if (node->type == Pipe)
			last_pcall = NULL;
		else if (node->type == Redirect_input \
		|| node->type == Redirect_input_heredoc)
		{
			if (last_pcall)
				shift_back(node, last_pcall);
		}
		node = node->output;
	}
	return (head);
}
