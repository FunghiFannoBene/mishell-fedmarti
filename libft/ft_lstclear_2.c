/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:20:25 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/19 20:21:10 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_2(t_list **lst, void (*del)(void *, void *), void *arg)
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if (del)
			del((*lst)->content, arg);
		free(*lst);
		*lst = temp;
	}
	lst = NULL;
}
