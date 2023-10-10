/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_up_to.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:23:15 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/10 21:23:48 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	is_(char c, char *charset)
{
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
	temp = str;
	while (!is_(*temp, stop_charset))
		temp++;
	copy = malloc(str - temp + 1);
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, str, str - temp);
	return (copy);
}
