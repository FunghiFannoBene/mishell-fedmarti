/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:10:17 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/17 20:54:45 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include <sys/types.h>

typedef enum e_pnode_type
{
	Null,
	Program_Call,
	//|
	Pipe,
	//<
	Redirect_input,
	//<<
	Redirect_input_heredoc,
	//>
	Redirect_output,
	//>>
	Redirect_output_append
}	t_ntype;

typedef struct s_minishell_data	t_data;

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
void	free_node(t_pnode *node);
void	free_tree(t_pnode *head);
t_pnode	*node_create(enum e_pnode_type type, char **args, t_pnode *previous);
pid_t	run_command(t_pnode *node, t_data *data);
t_pnode	*next(t_pnode *node);
t_pnode	*del_next(t_pnode *node);
void	ft_exit(int exit_status, t_pnode *tree, t_data *data);
pid_t	ft_fork(int *exit_status);
int		on_return(int exit_status, t_pnode *node, int fd1, int fd2);

#endif