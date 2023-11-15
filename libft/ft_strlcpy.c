/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:27:32 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/15 23:26:19 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char	*d;
	size_t	len;

	d = dst;
	len = ft_strlen(src);
	if (!size)
		return (len);
	while (--size && *src)
		*d++ = *src++;
	*d = 0;
	return (len);
}
