/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:00:35 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/23 03:33:42 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdbool.h>

bool	ft_is_in_list(t_list *list, void *content, size_t content_size)
{
	while (list)
	{
		if (!ft_memcmp(list->content, content, content_size))
			return (true);
		list = list->next;
	}
	return (false);
}
