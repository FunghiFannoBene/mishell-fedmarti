/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:44:53 by shhuang           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/22 12:52:19 by shhuang          ###   ########.fr       */
=======
/*   Updated: 2023/11/24 00:26:43 by fedmarti         ###   ########.fr       */
>>>>>>> 07827eec2f8ba2deed0d513634b8f04ea3b81e48
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

int	check_all_end(char *s, int *i, t_redirect **command, int *variabile)
{
	*variabile = end_check(s, i, command);
	if (*variabile == -1)
		return (-2);
	else if (*variabile == -2)
		return (-1);
	else if (*variabile == -3)
		return (0);
	*variabile = flag_zero_space(s, i, command);
	if (*variabile == -1)
		return (-2);
	if (*variabile == -2)
		return (1);
	return (2);
}

int	size_of_command(char *s, int *i, t_redirect **head, t_pnode *structure)
{
	t_redirect	*command;
	int			variabile;

	init_size_of_command(structure, &command, head, i);
	while (s[*i])
	{
		if (skip_and_endstring(s, i))
			return (-1);
		if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
			return (0);
		if (assign_flag(s, i, &command) == -1)
			continue ;
		while (s[*i])
		{
			if (check_slashes(s, i, &command) == -1)
				continue ;
			variabile = check_all_end(s, i, &command, &variabile);
			if (variabile == -1 || variabile == 0 || variabile == 1)
				return (variabile);
			else if (variabile == -2 || break_or_add(s, i, command))
				break ;
		}
	}
	return (1);
}

void	free_t_pnode_list(t_pnode *structure_head)
{
	t_pnode	*current;
	t_pnode	*next_node;
	char	**current_args;
	int		i;

	i = -1;
	next_node = NULL;
	current = structure_head;
	while (current != NULL)
	{
		next_node = current->output;
		current_args = current->args;
		if (current_args != NULL)
		{
			while (current_args[++i] != NULL)
			{
				free(current_args[i]);
			}
			free(current_args);
		}
		free(current);
		current = next_node;
	}
}

int	init_command(t_command *c, char *s)
{
	c->command = NULL;
	c->structure_head = NULL;
	c->structure_actual = NULL;
	c->command_record = 0;
	c->status = 0;
	c->head = NULL;
	c->i = 0;
	if (!s)
		return (-1);
	return (1);
}

int	check_continuation(char *s, t_command *c)
{
	if (s[c->i] == '\0')
		return (1);
	c->command = NULL;
	c->head = NULL;
	c->structure = ft_calloc(1, sizeof(t_pnode));
	return (0);
}
