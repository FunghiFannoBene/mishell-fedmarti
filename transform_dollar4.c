/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dollar4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:05:01 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/17 03:57:35 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

int check_virgolette_doppie(char *s, int i)
{
	int count_double = 0;
	int x = i;
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

char *check_and_addx(char *start, char *tmp, char *position)
{
	char *result;

	result = NULL;
	if(check_virgolette_doppie(start, 0) == -1)
		result = ft_multistrjoin((char *[]){start, tmp, position, NULL});
	else
		result = ft_multistrjoin((char *[]){start, "'", tmp, "'", position, NULL});
	return(result);
}