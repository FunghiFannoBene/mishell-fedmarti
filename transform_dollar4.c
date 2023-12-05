/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dollar4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:20:47 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/05 23:31:01 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

int	check_virgolette_doppie(char *s, int i)
{
	int	count_double;
	int	x;

	count_double = 0;
	x = i;
	while (s[x])
	{
		if (s[x] == '"' && !(s[x] == '\\' && s[x + 1] == '"'))
			count_double++;
		x++;
	}
	if (count_double % 2)
		return (-1);
	return (0);
}

char	*check_and_addx(char *start, char *tmp, char *position, int *di)
{
	char	*result;

	result = NULL;
	if ((check_virgolette_doppie(start, 0) == -1))
	{
		result = ft_multistrjoin((char *[]){start, tmp, position, NULL});
		(*di)--;
	}
	else
	{
		result = ft_multistrjoin((char *[]){start, "'", tmp,
				"'", position, NULL});
		(*di)++;
	}
	return (result);
}

void	init_transform_d(t_short_dollar *d)
{
	d->tmp = NULL;
	d->i = -1;
	d->env_len = 0;
	d->save = 0;
	d->save_pre = 0;
	d->size = 0;
	d->slash_count = 0;
	d->start = 0;
	d->flag = 0;
}

int	contains_only_one_virgoletta(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			count++;
		if (count >= 2 || (s[i] != ' ' && s[i] != '\'' && s[i] != '"'))
			return (0);
		i++;
	}
	return (1);
}
