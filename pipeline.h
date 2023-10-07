/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:10:17 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/07 23:33:02 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

typedef enum e_pnode_type
{
	Null,
	Program_Call,
	Pipe,
	Redirect_input,
	Redirect_input_heredoc,
	Redirect_output,
	Redirect_output_append
}	t_ntype;

typedef struct s_pipeline_tree_node {
	enum e_pnode_type			type;
	char						**args;
	int							input_fd;
	int							output_fd;
	struct s_pipeline_tree_node	*input[2];
	struct s_pipeline_tree_node	*output;
}	t_pnode;

t_pnode	*sort_pipeline_tree(t_pnode *input_tree);
int		is_type(t_pnode *node, t_ntype *types);

#endif