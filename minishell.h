/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:47:13 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/07 22:43:44 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h> //path max
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <signal.h>

typedef struct s_list_env
{
	char				*env;
	struct s_list_env	*next;
}	t_env;

typedef struct s_shell_var {
	char	*name;
	char	*value;
}	t_var;

typedef struct s_env_pointer
{
	struct s_list_env	*head;
	struct s_list_env	*last;
}	t_env_pointer;

typedef struct s_minishell_data {
	t_list	*export_var;
	t_list	*local_var;
	t_var	*exit_status;
}	t_data;

t_var	*new_var(char *name, char *value);
void	free_var(void *variable);
t_var	*get_var(char *name, t_list *list);
int		set_var(t_var *var, char *new_value);
int		set_var_list(char *name, char *value, t_list *list);
t_list	*get_env_list(const char **env);
int		ft_export(char **args, t_data *data);
int		ft_env(t_list	*env_list);
int		ft_cd(char **args, t_data *data);
int		ft_pwd(char	**args, t_data *data);
int		ft_unset(char **args, t_data *data);
int		ft_heredoc(char **args, int fd);

#endif