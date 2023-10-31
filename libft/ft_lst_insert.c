/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:33:19 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/17 19:36:14 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_insert_when(t_list **list, \
t_list *new_node, bool (*comparison)(void *, void *))
{
	t_list	*temp_node;
	t_list	*prev_node;

	temp_node = *list;
	prev_node = NULL;
	while (temp_node && !comparison(new_node->content, temp_node->content))
	{
		prev_node = temp_node;
		temp_node = temp_node->next;
	}
	if (!prev_node)
		*list = new_node;
	else
		prev_node->next = new_node;
	new_node->next = temp_node;
}

void	ft_lst_insert_n(t_list **list, t_list *new, unsigned short n)
{
	unsigned short	i;
	t_list			*temp;
	t_list			*prev;

	temp = *list;
	prev = NULL;
	i = 0;
	while (temp && i != n)
	{
		prev = temp;
		temp = temp->next;
		i++;
	}
	if (!prev)
		*list = new;
	else
		prev->next = new;
	new->next = temp;
}
