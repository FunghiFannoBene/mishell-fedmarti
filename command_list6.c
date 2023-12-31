/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:44:00 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/16 02:16:25 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

int	end_check(char *s, int *i, t_redirect **command)
{
	if (!s)
		return (0);
	if (s[*i] == (*command)->flag && s[*i - 1] != '\\')
	{
		(*i)++;
		add_and_set_for_next(command, s);
		if (s[*i] == ' ' || s[*i] == '\0')
			(*command)->status = 0;
		else
			(*command)->status = 1;
		check_and_skip_space(s, i);
		(*command)->start = *i;
		if (s[*i] == '\0')
		{
			(*command)->next = NULL;
			return (-2);
		}
		return (-1);
	}
	return (end_check_flag_zero(s, i, command));
}

int	flag_zero_space(char *s, int *i, t_redirect **command)
{
	if ((*command)->flag == 0 && s[*i] == ' ')
	{
		(*command)->next = ft_calloc(sizeof(t_redirect), 1);
		(*command)->next->str = substring(s, (size_t)(*command)->start,
				(size_t)(*command)->size);
		(*command) = (*command)->next;
		(*command)->flag = 0;
		(*command)->size = 0;
		(*command)->status = 0;
		check_and_skip_space(s, i);
		(*command)->start = *i;
		if (s[*i] == '\0' || s[*i] == '|' || s[*i] == '>' || s[*i] == '<')
		{
			(*command)->next = NULL;
			return (-2);
		}
		return (-1);
	}
	return (1);
}

void	init_size_of_command(t_pnode *structure, t_redirect **command,
		t_redirect **head, int *i)
{
	*command = *head;
	if (structure->type == Null)
		structure->type = Program_Call;
	(*command)->flag = 0;
	(*command)->start = *i;
	(*command)->size = 0;
	(*command)->status = 0;
}

int	break_or_add(char *s, int *i, t_redirect *command)
{
	if (command->flag == 0 && (s[*i] == '\'' || s[*i] == '"'))
		return (1);
	if (command->flag == 0 && s[*i] == ' ')
	{
		(*i)++;
		return (1);
	}
	command->size++;
	(*i)++;
	return (0);
}

int	skip_and_endstring(char *s, int *i)
{
	check_and_skip_space(s, i);
	if (s[*i] == '\0')
		return (1);
	return (0);
}
