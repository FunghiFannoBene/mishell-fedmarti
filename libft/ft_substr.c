/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:33:02 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/10 21:55:19 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start > i)
		start = i;
	if (i - start < len)
		len = i - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	s += start;
	while (*s && i < len)
	{
		sub[i] = *s;
		s++;
		i++;
	}
	sub[i] = 0;
	return (sub);
}
