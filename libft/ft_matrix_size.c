/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:27:05 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/19 20:29:55 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//please pass a null terminated 2d array
size_t	ft_matrix_size(void **mat)
{
	size_t	i;

	if (!mat)
		return (0);
	i = 0;
	while (mat[i] != NULL)
		i++;
	return (i);
}
