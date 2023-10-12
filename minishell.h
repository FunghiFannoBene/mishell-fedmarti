/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:47:13 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/13 00:36:12 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h> //path max
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# ifndef NOT_VALID
#  define NOT_VALID "!@#$%^*=+~,.;:\" "
# endif

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
char	*search_variable(char *str, t_data *data);
t_var	*search_variable_tvar(char *str, t_data *data);
char	*expand_variables(char *str, t_data *data);
int		set_var(t_var *var, char *new_value);
int		set_var_list(char *name, char *value, t_list *list);
t_list	*get_env_list(const char **env);
char	**env_list_to_array(t_list *env_list);
int		ft_export(char **args, t_data *data, int fd);
int		ft_env(t_list *env_list, int fd);
int		ft_cd(char **args, t_data *data);
int		ft_pwd(char	**args, t_data *data);
int		ft_unset(char **args, t_data *data);
int		ft_heredoc(char **args, int fd, t_data *data);

//quick function to print the error message and returns the exit value
int		no_such_file_or_directory(char *filename);

//takes filename string and the PATH env variable
//returns value:
//name if NULL or if it's already either written as absolute/relative path
//allocated string with absolute path to name if it's found within PATH
//NULL if there's no name file in the directories pointed to by PATH
char	*find_file_in_path(char *name, t_var *env_v_path);

#endif