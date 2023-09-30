/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_swap_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:21:22 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/02 00:29:10 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

//swaps node with node node->next and returns node->next
t_list	*ft_lst_swap_next(t_list *node)
{
	t_list	*next;
	t_list	*second_next;

	if (!node)
		return (NULL);
	if (!node->next)
		return (node);
	next = node->next;
	second_next = next->next;
	next->next = node;
	node->next = second_next;
	return (next);
}
