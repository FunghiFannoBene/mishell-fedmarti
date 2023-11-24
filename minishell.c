/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:14:43 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/24 01:13:55 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// IMPLEMENTARE: strcmp, strncmp
#include "minishell.h"
#include "pipeline.h"
#include "short_code.h"

void	update_exit_status(t_var *exit_status, int new_val);

int clear()
{
	// write(STDOUT_FILENO, "\033[H\033[2J\033[3J", 11);
	// write(STDOUT_FILENO, "\033[H\033[2J\033[3J", 12);
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
	data->exit_status = new_var("?", "666");
	if (!data->exit_status)
	{
		free(data);
		return (NULL);
	}
	update_exit_status(data->exit_status, 0);
	data->export_var = get_env_list((const char **)env);
	if (!data->export_var)
	{
		free(data->exit_status);
		free(data);
		return (NULL);
	}
	return (data);
}

void	update_exit_status(t_var *exit_status, int new_val)
{
	int	pow;
	int	i;

	ft_bzero(exit_status->value, sizeof(char) * 4);
	if (!new_val)
	{
		exit_status->value[0] = '0';
		return ;
	}
	pow = 1;
	i = 0;
	while (pow * 10 < new_val)
		pow *= 10;
	while (pow)
	{
		exit_status->value[i] = new_val / pow % 10 + '0';
		i++;
		pow /= 10;
	}
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
	t_data	*data;

	printf("minishell pid: %i\n", getpid());
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
			write (1, "exit\n", 6);
			ft_exit((char *[]){"exit", NULL}, data);
		}
		add_history(input); // aggiunge alla storia da solo! non serve la struct
		// char *temp = input;
		input = transform_for_dollar(input, data);
		// free(temp);
		if (!input)
		{
			write(2, "Malloc error\n", 14);
			free_data(data);
			return (1);
		}
		t_pnode *command_list = create_command_list(input);
		// int i = 0;
		// while(command_list)
		// {
		// 	while(command_list->args)
		// 		printf("|%s|\n", command_list->args[i++]);
		// 	command_list = command_list->output;
		// }
		free (input);
		int es = run_command_pipeline(command_list, data);
		update_exit_status(data->exit_status, es);
	}
	free_data(data);
	return (0);
}
