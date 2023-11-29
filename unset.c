/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:36:51 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/29 19:41:15 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_var(char *name, t_list **list)
{
	t_list	*prev;
	t_list	*node;
	int		name_len;

	if (!name || !list || !*list)
		return ;
	node = *list;
	prev = NULL;
	name_len = ft_strlen(name);
	while (node)
	{
		if (!ft_strncmp(name, ((t_var *)node->content)->name, name_len))
		{
			if (prev)
				prev->next = node->next;
			else
				*list = node->next;
			ft_lstdelone(node, free_var);
			return ;
		}
		prev = node;
		node = node->next;
	}
}

// static void	wrong_character_error(char *str)
// {
// 	char	*error_message;

// 	error_message = ft_multistrjoin((char *[]){"bash: unset: `", 
// 	str, "\': not a valid identifier\n", NULL});
// 	if (!error_message)
// 		return ;
// 	write (2, error_message, ft_strlen(error_message));
// 	free (error_message);
// }

int	ft_unset(char **args, t_data *data)
{
	int	i;
	int	return_val;

	return_val = 0;
	if (args[0] && !args[1])
	{
		write (2, "unset: not enough arguments\n", 29);
		return (130);
	}
	i = 1;
	while (args[i])
	{
		if (get_var(args[i], data->export_var))
			remove_var(args[i], &data->export_var);
		i++;
	}
	return (return_val);
}
