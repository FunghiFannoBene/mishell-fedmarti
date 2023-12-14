/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list12.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:43:41 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/14 13:28:56 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

int	create_command_size2(char *s, int *i, t_redirect **command, t_search *k)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	k->head = *command;
	k->start = *i;
	while (s[k->start + k->x] && s[k->start + k->x] != ' '
		&& s[k->start + k->x] != '|'
		&& s[k->start + k->x] != '<'
		&& s[k->start + k->x] != '>'
		&& s[k->start + k->x] != '\''
		&& s[k->start + k->x] != '"')
		k->x++;
	while (((s[k->start + k->x] != '\'' && k->single_double == 1)
			&& (s[k->start + k->x] != '"'
				&& k->single_double == 2)))
		k->x++;
	(*command)->str = ft_calloc((size_t)(k->x) + 1, 1);
	if (!(*command)->str)
		return (1);
	return (0);
}

void	alloc_command_size2(char *s, int *i, t_redirect **command, t_search *k)
{
	k->x = 0;
	while (s[*i] && s[*i] != ' ' && s[*i] != '|' && s[*i] != '<' && s[*i] != '>'
		&& (s[*i] != '\'' && s[*i] != '"'))
		(*command)->str[k->x++] = s[(*i)++];
	while (((s[*i] != '\'' && k->single_double == 1) && (s[*i] != '"'
				&& k->single_double == 2)))
		(*command)->str[k->x++] = s[(*i)++];
	(*command)->str[k->x] = '\0';
	(*command)->size = k->x;
	(*command)->flag = 0;
	if (k->single_double)
		(*i)++;
	while (s[*i] && s[*i] == ' ')
		(*i)++;
}

int	check_endstr(t_redirect **command, t_pnode **structure, int *i, char *s)
{
	if (s[*i] == '\0')
	{
		(*command)->next = NULL;
		if ((*structure)->type == Null)
			(*structure)->type = Program_Call;
		return (1);
	}
	return (0);
}
