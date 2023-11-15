/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:04:19 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/15 23:26:50 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s_len;
	size_t	d_len;
	char	*d;

	if (!src)
		return (0);
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (d_len >= size)
		return (size + s_len);
	d = dst + d_len;
	size -= d_len + 1;
	while (size-- && *src)
		*d++ = *src++;
	*d = 0;
	return (d_len + s_len);
}
