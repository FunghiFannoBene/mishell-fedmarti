/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:05:48 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/20 15:27:09 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//frees matrix and its content
//it is good practice not to count the last pointer if null terminated
void	*ft_free_matrix(void ***pointer, size_t n_members)
{
	size_t	i;

	i = 0;
	if (!*pointer)
		return (NULL);
	while (i < n_members)
	{
		if ((*pointer)[i])
			free((*pointer)[i]);
		i++;
	}
	free(*pointer);
	*pointer = NULL;
	return (NULL);
}
