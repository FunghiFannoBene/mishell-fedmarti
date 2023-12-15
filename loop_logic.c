/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 00:35:56 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/15 20:48:20 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"
#include "short_code.h"

char	*transform_for_dollar(char *s, t_data *data);
t_pnode	*create_command_list(char *s);
int		run_command_pipeline(t_pnode *pipeline_tree, t_data *data);
void	free_data(t_data *data);

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

void free_command_list(t_pnode **command_list) {
    t_pnode *current;
    t_pnode *next;

    current = *command_list;
    while (current != NULL) {
        next = current->output;
        if (current->args != NULL) {
            free_matrix(&(current->args));
        }
        free(current);
        current = next;
    }
    *command_list = NULL;
}

void	prompt_loop(t_data *data)
{
	char	*input;
	t_pnode	*command_list;
	int		exit_status;

	input = readline("Minishell>");
	if (!input)
		ft_exit((char *[]){"exit", NULL}, data, NULL);
	add_history(input);
	input = transform_for_dollar(input, data);
	if (!input)
	{
		write(2, "Malloc error\n", 13);
		free_data(data);
		exit (1);
	}
	command_list = create_command_list(input);
	// free_command_list(&command_list);
	free (input);
	// exit(0); //aggiunto per test
	if (!command_list)
		exit_status = 0;
	else
		exit_status = run_command_pipeline(command_list, data);
	update_exit_status(data->exit_status, exit_status);
}
