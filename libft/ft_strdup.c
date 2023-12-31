/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:11:59 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/30 19:28:22 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup_str;

	if (!s)
		return (NULL);
	dup_str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dup_str)
		return (NULL);
	i = 0;
	while (*s)
	{
		dup_str[i] = *s;
		s++;
		i++;
	}
	dup_str[i] = 0;
	return (dup_str);
}
