/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:41:52 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/19 11:02:00 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

// int	check_virgolette_dispari_start(char *s, int i)
// {
// 	int	count_double;
// 	int	count_single;
// 	int	x;

// 	count_double = 0;
// 	count_single = 0;
// 	x = i;
// 	while (s[x])
// 	{
// 		if (s[x] == '\'' &&  (x >= 1 && !(s[x-1] == '\\' && s[x] == '\'')))
// 		{
// 			count_single++;
// 			while(s[x] && !(s[x-1] != '\\' && s[x] == '\''))
//     			x++;
// 		}
// 		else if (s[x] == '"' && (x >= 1 && !(s[x-1] == '\\' && s[x] == '"')))
// 			count_double++;
// 		x++;
// 	}
// 	if (count_double % 2 || count_single % 2)
// 		return (-1);
// 	return (0);
// }

void	init_search(t_search *k, t_redirect **command, char *s, int *i)
{
	k->x = 0;
	k->rx = 0;
	k->start = 0;
	k->head = NULL;
	k->single_double = 0;
	*command = malloc(sizeof(t_redirect));
	memset((*command), 0, sizeof(t_redirect));
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
		printf("bash: syntax error near unexpected token `>'\n");
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
	(*command)->str = malloc((size_t)k->x + 1);
	if (!(*command)->str)
		return (1);
	return (0);
}
