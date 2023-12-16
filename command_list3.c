/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:02:26 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/16 01:08:01 by shhuang          ###   ########.fr       */
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
	*command = ft_calloc(sizeof(t_redirect), 1);
	while (s[*i] && s[*i] == ' ')
		(*i)++;
}

int	check_zero_move(char *s, int *i, t_redirect **command)
{
	if (s[*i] == '\0')
	{
		free(*command);
		return (1);
	}
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	return (0);
}

int	check_pipe_redi(char *s, int *i, t_redirect **command, t_pnode *structure)
{
	int	redir;

	if (check_pipe(s, i, structure))
	{
		free(*command);
		*command = NULL;
		return (-4);
	}
	redir = check_redirect(s, i, structure);
	if (redir == 1)
	{
		free(*command);
		write(2, "minishell: syntax error near unexpected token `>'\n", 50);
		return (-1);
	}
	else if (redir == 2)
		return (-2);
	return (0);
}

int	create_command_size(char *s, int *i, t_redirect **command)
{
	adapt_virgolette(s, command, i);
	if (!(*command)->str)
		return (1);
	return (0);
}
