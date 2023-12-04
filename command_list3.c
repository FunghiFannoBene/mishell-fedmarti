/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:02:26 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/04 16:12:57 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

void	init_search(t_search *k, t_redirect **command, char *s, int *i)
{
	k->x = 0;
	k->rx = 0;
	k->start = 0;
	k->head = NULL;
	k->single_double = 0;
	*command = ft_calloc(sizeof(t_redirect),1);
	while (s[*i] && s[*i] == ' ')
		(*i)++;
}

int	check_zero_move(char *s, int *i, t_redirect **command, t_search *k)
{
	if (s[*i] == '\0')
	{
		free(*command);
		return (1);
	}
	while ((s[*i] == '\'' && s[*i + 1] == '\'') || (s[*i] == '"' && s[*i
				+ 1] == '"'))
		(*i) += 2;
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	check_virgolette_dispari(s, i);
	if (s[*i] == '\'')
	{
		(*i)++;
		k->single_double = 1;
	}
	if (s[*i] == '"')
	{
		k->single_double = 2;
		(*i)++;
	}
	return (0);
}

int	check_pipe_redi(char *s, int *i, t_redirect **command, t_pnode *structure)
{
	if (check_pipe(s, i, structure))
	{
		free(*command);
		*command = NULL;
		return (-4);
	}
	if (check_redirect(s, i, structure))
	{
		free(*command);
		write(2, "minishell: syntax error near unexpected token `>'\n", 50);
		return (-1);
	}
	return (0);
}

int	create_command_size(char *s, int *i, t_redirect **command, t_search *k)
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
