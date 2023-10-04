/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:14:43 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/04 23:23:29 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// IMPLEMENTARE: strcmp, strncmp
#include "minishell.h"

void clear()
{
	write(STDOUT_FILENO, "\033[H\033[2J\033[3J", 11); 
	//esegue clear "\033[H" si muove a HOME , "\033[2J" pulisce 
	//l'area attuale "\033[3J" pulisce anche la history
}

void print_env(char **env)
{
	for (int i = 0; env[i]; i++)
		printf("%s ", env[i]);
}

void print_env_var(char **env, char *var)
{
	for (int i = 0; env[i]; i++)
	{
		if (!strncmp(env[i], var, strlen(var)))
			printf("%s\n", env[i]);
	}
}

t_data	*data_init(char **env)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(*data));
	if (!data)
		return (NULL);
	data->exit_status = new_var("?", "0");
	if (!data->exit_status)
	{
		free(data);
		return (NULL);
	}
	data->export_var = get_env_list((const char **)env);
	if (!data->export_var)
	{
		free(data->exit_status);
		free(data);
		return (NULL);
	}
	// data->pwd = get_var("PWD");
	// data->old_pwd = get_var("OLDPWD");
	// data->home = get_var("HOME");
	// data->path = get_var("PATH");
	return (data);
}

int main(int argc, char **argv, char **env) 
{
    char	*input;
	char	**args;
	t_data	*data;

	data = data_init(env);
	if (!data)
		return (1);
	(void)argc;
	(void)argv;
	clear(); //pulisce all'avvio
    while (1) {
		// print_env(env);
        input = readline("Minishell> "); //stampa e aspetta un input
		args = ft_split(input, ' ');
		if (!args || !args[0])
		{
			ft_free_matrix((void ***)&args, INT_MAX);
			continue ;
		}
		else if (ft_strncmp(args[0], "exit", 5) == 0)
			exit(0);
		else if (ft_strncmp(args[0], "clear", 6) == 0)
			clear();
		else if (ft_strncmp(args[0], "cd", 3) == 0)
			ft_cd(args, data);
		else if (ft_strncmp(args[0], "pwd", 4) == 0)
			ft_pwd(args, data);
		else if (ft_strncmp(args[0], "export", 7) == 0)
			ft_export(args, data->export_var);
		else if (ft_strncmp(args[0], "env", 4) == 0)
			ft_env(data->export_var);
		else if (ft_strncmp(args[0], "echo", 5) == 0)
			printf("echo not implemented yet");
		else if (ft_strncmp(args[0], "unset", 6) == 0)
			ft_unset(args, data);
		add_history(input); // aggiunge alla storia da solo! non serve la struct
		free (input);
		ft_free_matrix((void ***)&args, INT_MAX);
	}
	ft_free_matrix((void ***)&args, INT_MAX);
	free_var(data->exit_status);
	ft_lstclear(&data->export_var, free_var);
	free(data);
	return (0);
}
