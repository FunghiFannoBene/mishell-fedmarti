/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:10:17 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/25 17:13:48 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include <sys/types.h>

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

typedef struct s_minishell_data	t_data;

typedef struct s_pipeline_tree_node
{
	enum e_pnode_type			type;
	char						**args;
	int							input_fd;
	int							output_fd;
	struct s_pipeline_tree_node	*input[2];
	struct s_pipeline_tree_node	*output;
	pid_t						pid;
}	t_pnode;

typedef struct s_redirect
{
	char				*str;
	struct s_redirect	*next;
	int					start;
	char				flag;
	int					size;
	int					status;
}	t_redirect;

typedef struct s_fix_string
{
	char					*command_name;
	char					*stringa;
	struct list_redirect	*redirect;
	struct s_fix_string		*next;
}	t_indice;

// void	next_size(char *s, int *i, t_redirect **command);
t_pnode	*sort_pipeline_tree(t_pnode *input_tree);
int		is_type(t_pnode *node, t_ntype *types);
void	free_node(t_pnode *node);
void	free_tree(t_pnode *head);
t_pnode	*node_create(enum e_pnode_type type, char **args, t_pnode *previous);
pid_t	run_command(t_pnode *node, t_data *data);
t_pnode	*next(t_pnode *node);
t_pnode	*del_next(t_pnode *node);
void	ft_exit_pip(int exit_status, t_pnode *tree, t_data *data);
pid_t	ft_fork(int *exit_status);
int		on_return(int exit_status, t_pnode *node, int fd1, int fd2);
char	*transform_for_dollar(char *s, t_data *data);
// char	*replace_for_new_str(char *s, char *tmp, int i, int size);
// char	*add_slashes(char *tmp);
// int		checksymbol(char *s);
int		check_invalid(char c, char *invalid);
// char	*ft_strndup(const char *s, size_t n);]
int		is_builtin(char *str);
int		ft_builtin(t_pnode *node, t_data *data);

#endif
