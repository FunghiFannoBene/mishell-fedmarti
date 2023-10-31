/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:23:35 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 18:23:45 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//searches content through list and removes it if it's found, returning it
t_list	*ft_lstpop_one(void *content, t_list **list)
{
	t_list	*temp;
	t_list	*prev;

	prev = NULL;
	temp = *list;
	while (temp)
	{
		if (temp->content == content)
		{
			if (prev)
				prev->next = temp->next;
			else
				*list = temp->next;
			return (temp);
		}
		prev = temp;
		temp = temp->next;
	}
	return (NULL);
}
