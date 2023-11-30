/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:14:43 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/30 16:25:32 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

void	prompt_loop(t_data *data);
void	update_exit_status(t_var *exit_status, int new_val);

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
