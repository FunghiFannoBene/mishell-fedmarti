/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:00:47 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/30 18:15:50 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//returns a null terminated 2d array
//each pointer of the void ** array points to the content of each list node
//also frees the list
void	**ft_lst_to_matrix(t_list *lst)
{
	size_t	i;
	size_t	len;
	t_list	*temp_node;
	void	**mat;

	i = 0;
	len = (size_t)ft_lstsize(lst) + 1;
	mat = ft_calloc(len, sizeof(void *));
	if (!mat)
		return (NULL);
	while (i < len - 1)
	{
		mat[i] = lst->content;
		temp_node = lst;
		lst = lst->next;
		free(temp_node);
		i++;
	}
	return (mat);
}
