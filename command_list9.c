/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list9.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:33:41 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/23 15:15:53 by shhuang          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "short_code.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*joint;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1) + ft_strlen(s2);
	joint = (char *)malloc(((len + 1) * sizeof(char)));
	if (!joint)
		return (NULL);
	i = 0;
	while (len-- && *s1)
	{
		joint[i] = *s1;
		s1++;
		i++;
	}
	len++;
	while (len-- && *s2)
	{
		joint[i] = *s2;
		s2++;
		i++;
	}
	free(s1);
	joint[i] = 0;
	return (joint);
}

// int close_at_flag(char *str, int *i, char flag)
// {
// 	int x = *i;
// 	while(str[x])
// 	{
// 		if(str[x] == flag && i > 0 && !str[x-1] != '\\')
// 			return(x);
// 		*i++;
// 	}
// 	return(0);
// }

