/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:14:43 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/16 01:21:01 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

void	prompt_loop(t_data *data);
void	update_exit_status(t_var *exit_status, int new_val);

void	update_env_vars(t_data *data)
{
	t_var	*shell_level;
	char	*level;

	shell_level = get_var("SHLVL", data->export_var);
	if (!shell_level)
		set_var_list("SHLVL", "1", data->export_var);
	else
	{
		level = ft_itoa(ft_atoi(shell_level->value) + 1);
		if (!level)
			return ;
		set_var_list("SHLVL", level, data->export_var);
		free(level);
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
	update_env_vars(data);
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

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	rl_outstream = stderr;
	data = data_init(env);
	if (!data)
		return (1);
	(void)argc;
	(void)argv;
	while (1)
		prompt_loop(data);
	free_data(data);
	return (0);
}
