/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list11.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:09:30 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/14 11:10:58 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

void	movestr(char *start, int *i)
{
	while (start[*i] && (start[*i] == '<' || start[*i] == '>'
			|| start[*i] == ' '))
		(*i)++;
}

int	find_len_redir(char *start, int *i, t_cs *stat)
{
	while (start[*i])
	{
		movestr(start, i);
		while (start[*i] && start[*i] != ' ')
		{
			if (start[*i] == '|' || start[*i] == '\0')
				return (0);
			if (start[*i] == '<' || start[*i] == '>')
				break ;
			(*i)++;
		}
		if (start[*i] == '<' || start[*i] == '>')
			continue ;
		else if (start[*i] == ' ')
		{
			stat->z = evaluate_command(start, i, stat);
			if (stat->z == 1)
				continue ;
			else if (stat->z == 2)
				return (0);
			return (1);
		}
	}
	return (0);
}

void	edit_s(char *use, char *s, t_cs stat)
{
	int	starter;

	starter = stat.start_r;
	while (starter < stat.end_c)
	{
		s[starter] = use[stat.start_c];
		starter++;
		stat.start_c++;
		if (stat.start_c == stat.end_c)
			break ;
	}
	while (starter < stat.end_c)
	{
		s[starter] = use[stat.start_r];
		starter++;
		stat.start_r++;
		if (stat.start_r == stat.start_c)
			break ;
	}
}

void	sort_redirorder(char *s)
{
	char	*use;
	t_cs	stat;

	use = ft_strdup(s);
	stat.i = 0;
	while (use[stat.i])
	{
		while (use[stat.i] && use[stat.i] == ' ')
			stat.i++;
		if (use[stat.i] == '<' || use[stat.i] == '>')
		{
			stat.start_r = stat.i;
			if (find_len_redir(use, &stat.i, &stat))
				edit_s(use, s, stat);
		}
		while (use[stat.i] && use[stat.i] != '|')
			stat.i++;
		if (!use[stat.i])
			break ;
		stat.i++;
	}
	free(use);
}
