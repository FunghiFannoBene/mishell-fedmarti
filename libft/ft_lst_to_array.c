/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 23:37:58 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/30 18:16:21 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//copies the content of a list to an array and frees the list
t_array	ft_lst_to_array(t_list **list, size_t member_size, void (*del)(void *))
{
	t_array	array;
	t_list	*temp;
	t_list	*node;
	size_t	i;

	array = (t_array){(void *)0, member_size, ft_lstsize(*list)};
	array.arr = ft_calloc(array.n_members, array.member_size);
	if (!array.arr)
	{
		ft_lstclear(list, del);
		return ((t_array){(void *)0, 0, 0});
	}
	node = *list;
	i = 0;
	while (i < array.n_members)
	{
		ft_memcpy(array.arr + member_size * i, node->content, member_size);
		temp = node;
		node = node->next;
		ft_lstdelone(temp, del);
		i++;
	}
	return (array);
}
