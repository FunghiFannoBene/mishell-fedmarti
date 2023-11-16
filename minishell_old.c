/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_old.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:14:43 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/16 18:51:13 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// IMPLEMENTARE: strcmp, strncmp
#include "minishell.h"
#include "pipeline.h"

int clear()
{
	write(STDOUT_FILENO, "\033[H\033[2J\033[3J", 11);z
	return (0);
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
	return (data);
}


void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->exit_status)
		free_var(data->exit_status);
	if (data->export_var)
		ft_lstclear(&data->export_var, free_var);
	free(data);
}

void	null_list_test(t_data *data)
{
	t_list *env = data->export_var;

	while (env)
	{
		t_list *temp = env->next;
		ft_unset((char *[]){"env", ((t_var *)env->content)->name, NULL}, data);
		env = temp;
	}
}

char 	*transform_for_dollar(char *s, t_data* data);
t_pnode *create_command_list(char *s);
int	run_command_pipeline(t_pnode *pipeline_tree, t_data *data);

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**args;
	t_data	*data;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	data = data_init(env);
	if (!data)
		return (1);
	(void)argc;
	(void)argv;
	clear(); //pulisce all'avvio
	while (1)
	{
        input = readline("Minishell> "); //stampa e aspetta un input
		if (!input)
		{
			write(1, "exit", 5);
			free_data(data);
			exit (0);
		}
		args = ft_split(input, ' '); //da sostutuire con parsing
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
			ft_export(args, data);
		else if (ft_strncmp(args[0], "env", 4) == 0)
			ft_env(data->export_var);
		else if (ft_strncmp(args[0], "echo", 5) == 0)
			printf("echo not implemented yet");
		else if (ft_strncmp(args[0], "unset", 6) == 0)
			ft_unset(args, data);
		else if (ft_strncmp(args[0], "nulllisttest", 13) == 0)
			null_list_test(data);//test temporaneo, svuota la lista env
		else if (ft_strncmp(args[0], "<<", 3) == 0)
			ft_heredoc((char *[]){args[1], NULL}, 1, data);
		add_history(input); // aggiunge alla storia da solo! non serve la struct
		free (input);
		ft_free_matrix((void ***)&args, INT_MAX);
	}
	ft_free_matrix((void ***)&args, INT_MAX);
	free_data(data);
	return (0);
}
