/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dollar4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:05:01 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/19 16:42:02 by shhuang          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

char *check_and_addx(char *start, char *tmp, char *position, int *di)
{
	char *result;

	result = NULL;
	if((check_virgolette_doppie(start, 0) == -1))
		result = ft_multistrjoin((char *[]){start, tmp, position, NULL});
		(*di)--;
	return(result);
}

char *remove_useless(char *s)
{
	char *newstr = ft_calloc(ft_strlen(s)+1 , 1);
	int i = 0;
	int x = 0;
	while(s[i])
	{
		if(s[i] == '"')
		{
			i++;
			while(s[i] && s[i] != '"')
			{
				newstr[x++] = s[i];
				i++;
			}
			if(s[i] == '\0')
				break;
		}
		else if(s[i] != '\'')
			newstr[x++] = s[i];
		i++;
	}
	newstr[x] = '\0';
	printf("\n\n%s\n\n", newstr);
	return(newstr);
}