/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:42:31 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/07 17:51:23 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

void	alloc_command_size(char *s, int *i, t_redirect **command, t_search *k)
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

int	search_command(char *s, int *i, t_redirect **command, t_pnode *structure)
{
	t_search	k;

	init_search(&k, command, s, i);
	if (check_zero_move(s, i, command, &k))
		return (-3);
	k.rx = check_pipe_redi(s, i, command, structure);
	if (k.rx != 0)
		return (k.rx);
	if (create_command_size(s, i, command, &k))
		return (-1);
	alloc_command_size(s, i, command, &k);
	if (s[*i] == '\0')
	{
		(*command)->next = NULL;
		if (structure->type == Null)
			structure->type = Program_Call;
		return (-2);
	}
	else
		next_size(i, &k.head);
	return (0);
}

int	check_and_skip_space(char *s, int *i)
{
	if (s[*i] == ' ')
	{
		while (s[*i] == ' ')
			(*i)++;
	}
	else
		return (-1);
	return (0);
}

int	assign_flag(char *s, int *i, t_redirect **command, char *h_c)
{
	if (s[*i] == '\'')
		(*command)->flag = '\'';
	else if (s[*i] == '"')
		(*command)->flag = '"';
	if ((*command)->flag != 0)
		(*i)++;
	if ((*command)->flag == s[*i])
	{
		if (ft_strncmp(h_c, "echo", 4) == 0
			&& s[*i + 1] == ' ' && s[*i - 2] == ' ')
		{
			(*command)->next = ft_calloc(sizeof(t_redirect), 1);
			*command = (*command)->next;
			(*command)->str = ft_calloc(1, 1);
			(*command)->next = NULL;
		}
		(*i)++;
		(*command)->flag = 0;
		return (-1);
	}
	(*command)->start = *i;
	return (1);
}

int	slash_return(char *s, int *i, t_redirect **command)
{
	if (((*command)->flag == 0 || (*command)->flag == '"')
		&& (s[*i] == '\\' && (s[*i + 1] == '\'' || s[*i + 1] == '"')))
	{
		(*command)->size++;
		(*i) += 2;
		if (s[*i] == '\0')
		{
			(*command)->start += 1;
			return (0);
		}
		return (-1);
	}
	return (0);
}
