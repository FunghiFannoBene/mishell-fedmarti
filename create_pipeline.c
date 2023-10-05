/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:03:32 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/06 00:14:08 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

int	create_pipeline(t_list *input, t_data *data)
{
	t_pnode	*current;

	(void)data;//
	while (input)
	{
		current = input->content;
		if (current->type == Program_Call)
			(void)current;//incomplete
		return (1);
	}
	//
}

int	is_type(t_pnode *node, t_ntype *types)
{
	int	i;

	i = 0;
	while (types[i] != Null)
	{
		if (node->type == *types)
			return (1);
		i++;
	}
	return (0);
}

t_pnode	*sort_pipeline_list(t_pnode *input_tree)
{
	t_pnode	*current;
	t_list	*tree_roots;

	if (!input_tree || !input_tree->output)
		return (input_tree);
	if (input_tree->type == Program_Call \
	&& (input_tree->output->type == Redirect_input \
	|| input_tree->output->type == Redirect_input_heredoc))
	{
		input_tree->
	}

	}
}