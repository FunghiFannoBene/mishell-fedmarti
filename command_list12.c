/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list12.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:43:41 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/16 01:58:13 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

void	first_word_virgolette(char *s, int i, int x)
{
	char	*r;
	int		flag;

	flag = 0;
	r = ft_strdup(s);
	if (r == NULL)
		return ;
	ft_bzero(s, ft_strlen(s));
	while (r[i] && r[i] != ' ')
	{
		if (r[i] == '\'' || r[i] == '"')
		{
			flag = r[i++];
			while (r[i] && r[i] != flag)
				s[x++] = r[i++];
			if (r[i] == flag)
				i++;
		}
		else
			s[x++] = r[i++];
	}
	while (r[i])
		s[x++] = r[i++];
	free (r);
}

int	create_command_size2(char *s, int *i, t_redirect **command, t_search *k)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	k->head = *command;
	k->start = *i;
	first_word_virgolette(s + *i, 0, 0);
	while (s[k->start + k->x] && s[k->start + k->x] != ' ' && s[k->start
			+ k->x] != '|' && s[k->start + k->x] != '<' && s[k->start
			+ k->x] != '>')
		k->x++;
	(*command)->str = ft_calloc((size_t)(k->x) + 1, 1);
	if (!(*command)->str)
		return (1);
	return (0);
}

void	alloc_command_size2(char *s, int *i, t_redirect **command, t_search *k)
{
	k->x = 0;
	while (s[*i] && s[*i] != ' ' && s[*i] != '|' && s[*i] != '<'
		&& s[*i] != '>')
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

int	found_virgoletta2(char *s, int *i, char *new, int *x)
{
	char	virgoletta;

	virgoletta = 0;
	if (s[*i] == '\'' || s[*i] == '"')
	{
		virgoletta = s[*i];
		(*i)++;
		while (s[*i] && s[*i] != virgoletta)
		{
			new[(*x)++] = s[(*i)++];
		}
		if (s[*i] == '\0' || s[*i] == ' ' || s[*i] == '<' || s[*i] == '>'
			|| s[*i] == '|')
			return (1);
		(*i)++;
		if (s[*i] == '\0' || s[*i] == ' ' || s[*i] == '<' || s[*i] == '>'
			|| s[*i] == '|')
			return (1);
	}
	return (0);
}
