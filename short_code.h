/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_code.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:13:22 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/05 22:56:05 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHORT_CODE_H
# define SHORT_CODE_H

# include "minishell.h"
# include "pipeline.h"
# include "libft/libft.h"

typedef struct s_short_dollar
{
	int			env_len;
	int			save;
	int			save_pre;
	int			size;
	int			slash_count;
	int			start;
	int			flag;
	int			i;
	char		*tmp;

}				t_short_dollar;

typedef struct s_replace
{
	int			env_len;
	char		*str;
	char		*result;
	char		*start;
	int			x;
}				t_replace;

typedef struct s_slashes
{
	int			i;
	int			count;
	int			x;
	char		*str;
}				t_slashes;

typedef struct s_command
{
	t_redirect	*command;
	t_redirect	*head;
	t_pnode		*structure;
	t_pnode		*structure_head;
	t_pnode		*structure_actual;
	t_redirect	*temp;
	int			i;
	int			x;
	int			command_record;
	int			type;
	int			status;
}				t_command;

typedef struct s_search
{
	int			x;
	int			start;
	t_redirect	*head;
	int			single_double;
	int			rx;
}				t_search;

int				check_invalid(char c, char *invalid);
int				checksymbol(char *s);
int				checksymbol2(char *s);
void			init_slashes(t_slashes *s);
void			run_count_slashes(char *tmp, t_slashes *s);
char			*add_slashes(char *tmp);
char			*ft_strndup(const char *s, size_t n);
void			init_replace(t_replace *r);
void			evaluate_free(char **tmp, char **s, t_replace *r);
char			*replace_for_new_str(char *s, char *tmp, int i, int *di);
void			init_transform_d(t_short_dollar *d);
int				create_flags(char *s, t_short_dollar *d);
char			*transform_for_dollar(char *s, t_data *data);
void			assign_redirection(int x, t_pnode *structure);
void			check_redirect_init(int *x, int *flag, int *count,
					t_pnode **structure);
int				check_redirect(char *s, int *i, t_pnode *structure);
int				check_pipe(char *s, int *i, t_pnode *structure);
int				check_virgolette_dispari(char *s, int *i);
void			init_search(t_search *k, t_redirect **command, char *s, int *i);
int				check_zero_move(char *s, int *i, t_redirect **command,
					t_search *k);
int				check_pipe_redi(char *s, int *i, t_redirect **command,
					t_pnode *structure);
int				create_command_size(char *s, int *i, t_redirect **command,
					t_search *k);
void			alloc_command_size(char *s, int *i, t_redirect **command,
					t_search *k);
int				search_command(char *s, int *i, t_redirect **command,
					t_pnode *structure);
int				check_and_skip_space(char *s, int *i);
int				assign_flag(char *s, int *i, t_redirect **command);
int				slash_return(char *s, int *i, t_redirect **command);
int				check_slashes(char *s, int *i, t_redirect **command);
char			*substring(const char *str, size_t begin, size_t len);
void			next_size(int *i, t_redirect **command);
void			add_and_set_for_next(t_redirect **command, char *s);
int				end_check_flag_zero(char *s, int *i, t_redirect **command);
int				end_check(char *s, int *i, t_redirect **command);
int				flag_zero_space(char *s, int *i, t_redirect **command);
void			init_size_of_command(t_pnode *structure, t_redirect **command,
					t_redirect **head, int *i);
int				break_or_add(char *s, int *i, t_redirect *command);
int				skip_and_endstring(char *s, int *i);
int				check_all_end(char *s, int *i, t_redirect **command,
					int *variabile);
int				size_of_command(char *s, int *i, t_redirect **head,
					t_pnode *structure);
void			free_t_pnode_list(t_pnode *structure_head);
int				init_command(t_command *c, char *s);
int				check_continuation(char *s, t_command *c);
void			assign_structure(t_command *c);
int				is_void(t_command *c);
int				evaluate_next_struct(t_command *c, char *s);
void			command_to_structure(t_command *c);
void			structure_linking(t_command *c);
t_pnode			*create_command_list(char *s);
char			*check_and_addx(char *start, char *tmp,
					char *position, int *di);
int				check_virgolette_doppie(char *s, int i);
char			*ft_strjoin2(char *s1, char *s2);
void			set_status(char *s, int i, int *status);
void			structure_linking(t_command *c);
int				is_void(t_command *c);
void			free_tmp_new_head(t_command **c);
void			init_transform_d(t_short_dollar *d);
int				contains_only_one_virgoletta(char *s);

#endif
