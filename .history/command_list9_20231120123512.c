/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list9.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:33:41 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/20 12:35:12 by shhuang          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "short_code.h"

char	*ft_strjoin2(char const *s1, char const *s2)
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
	joint[i] = 0;
	free(s1);
	return (joint);
}
