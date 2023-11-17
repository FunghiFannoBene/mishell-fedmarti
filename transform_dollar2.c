/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dollar2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:38:19 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/17 05:58:20 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

int	check_invalid(char c, char *invalid)
{
	int	i;

	i = 0;
	while (invalid[i])
	{
		if (invalid[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	checksymbol(char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (check_invalid(s[i], NOT_VALID) == 1)
			return (i);
		i++;
	}
	return (i);
}

int	checksymbol2(char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (check_invalid(s[i], NOT_VALID) == 1)
			return (i + 1);
		i++;
	}
	return (i + 1);
}

void	init_slashes(t_slashes *s)
{
	s->i = 0;
	s->count = 0;
	s->x = 0;
	s->str = NULL;
}

void	run_count_slashes(char *tmp, t_slashes *s)
{
	while (tmp[s->i])
	{
		if (tmp[s->i] == '\'' || tmp[s->i] == '"')
			s->count++;
		s->i++;
	}
	s->i = 0;
}
