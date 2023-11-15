/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:43:24 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/15 01:55:43 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../pipeline.h"
#include "short_code.h"

int	check_slashes(char *s, int *i, t_redirect **command)
{
	if (((*command)->flag == 0 || (*command)->flag == '"') && s[*i] == '\\'
		&& s[*i + 1] == '\\')
	{
		(*i) += 2;
		(*command)->size++;
		if (s[*i] == '\0')
			return (0);
		return (-1);
	}
	if (s[*i] == '\\' && s[*i + 1] == '$')
	{
		(*command)->size += 1;
		(*command)->start += 1;
		(*i) += 2;
		return (0);
	}
	return ((slash_return(s, i, command)));
}

char	*substring(const char *str, size_t begin, size_t len)
{
	if (str == NULL || ft_strlen(str) < begin || ft_strlen(str) < (begin + len))
		return (NULL);
	return (ft_strndup(str + begin, len));
}

void	next_size(int *i, t_redirect **command)
{
	(*command)->flag = 0;
	(*command)->start = *i;
	(*command)->size = 0;
}

void	add_and_set_for_next(t_redirect **command, char *s)
{
	(*command)->next = malloc(sizeof(t_redirect));
	memset((*command)->next, 0, sizeof(t_redirect));
	(*command)->next->str = substring(s, (*command)->start, (*command)->size);
	(*command) = (*command)->next;
	(*command)->flag = 0;
	(*command)->size = 0;
}

int	end_check_flag_zero(char *s, int *i, t_redirect **command)
{
	if ((*command)->flag == 0 && (s[*i] == '<' || s[*i] == '>'
			|| s[*i] == '|'))
	{
		add_and_set_for_next(command, s);
		(*command)->start = *i;
		return (-3);
	}
	else if (s[(*i) + 1] == '\0')
	{
		(*command)->size++;
		add_and_set_for_next(command, s);
		(*command)->next = NULL;
		(*i)++;
		return (-2);
	}
	else if ((*command)->flag == 0 && (s[*i] == '\'' || s[*i] == '"')
		&& (*command)->size)
	{
		(*i)++;
		add_and_set_for_next(command, s);
		return (-1);
	}
	return (0);
}
