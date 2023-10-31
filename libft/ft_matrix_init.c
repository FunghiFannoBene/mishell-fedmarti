/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:56:59 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/20 15:27:07 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_matrix_init(size_t x_size, size_t y_size, size_t member_size)
{
	void	**mat;
	size_t	i;

	mat = ft_calloc(y_size + 1, sizeof(void *));
	if (!mat)
		return (NULL);
	i = 0;
	while (i < y_size)
	{
		mat[i] = ft_calloc(x_size, member_size);
		if (!mat[i])
			return (ft_free_matrix(&mat, i));
		i++;
	}
	mat[i] = NULL;
	return (mat);
}
