/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iteri_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:01:44 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/20 15:27:06 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_iteri_2(t_list *list, void (*foo)(void *, void *), void *arg)
{
	while (list)
	{
		foo(list->content, arg);
		list = list->next;
	}
}
