/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dollar2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:38:19 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/29 22:45:07 by shhuang          ###   ########.fr       */
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

int	checksymbol(char *s)//crea un check che contolla se il primo carattere e' un numero (non valido) o un ? (valido)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 1;
	if(ft_isdigit(s[i]) || s[i] == '?')
		return(i);
	while (s[i] != '\0')
	{
		if (s[i] != '_' && !ft_isalnum(s[i]))
			return (i);
		i++;
	}
	return (i);
}

int	checksymbol2(char *s)//idem
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	if(ft_isdigit(s[i]) || s[i] == '?')
		return(i+2);
	while (s[i] != '\0')
	{
		if (s[i] != '_' && !ft_isalnum(s[i]))
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
