/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnext_and_delete.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:36:33 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/02 00:30:33 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnext_and_delete(t_list *node, void (*del)(void *))
{
	t_list	*temp;

	temp = node->next;
	if (del)
		del(node->content);
	free(node);
	return (temp);
}
