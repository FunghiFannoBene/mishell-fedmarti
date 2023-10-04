/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:05:48 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/04 18:48:20 by fedmarti         ###   ########.fr       */
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
	while (i < n_members && (*pointer)[i])
	{
		free((*pointer)[i]);
		i++;
	}
	free(*pointer);
	*pointer = NULL;
	return (NULL);
}
