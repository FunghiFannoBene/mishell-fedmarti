/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:24:04 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/25 18:25:44 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_array_free(t_array *arr, void (*del)(void *))
{
	size_t	i;

	if (!arr || !arr->arr)
		return ;
	if (del)
	{
		i = 0;
		while (i < arr->n_members)
		{
			del(arr->arr + i * arr->member_size);
			i++;
		}
	}
	free(arr->arr);
	*arr = (t_array){NULL, 0, 0};
}
