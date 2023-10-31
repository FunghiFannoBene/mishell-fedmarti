/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_up_to.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:23:15 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/11 00:51:31 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	is_(char c, char *charset)
{
	if (!c)
		return (0);
	while (charset && *charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

char	*ft_copy_up_to(char *str, char *stop_charset)
{
	char	*temp;
	char	*copy;

	if (!str)
		return (NULL);
	if (!stop_charset || !ft_strncmp(stop_charset, "", 1))
		return (ft_strdup(str));
	temp = str;
	while (*temp && !is_(*temp, stop_charset))
		temp++;
	copy = malloc(temp - str + 2);
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, str, temp - str + 1);
	return (copy);
}
