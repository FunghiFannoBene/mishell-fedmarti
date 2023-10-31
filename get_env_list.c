/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:26:50 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/09 01:32:45 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_name_field(const char *var)
{
	int		len;
	char	*name;
	int		i;

	len = 0;
	while (var[len] != 61 && var[len] != 0 && var[len] != 34 && var[len] != 39)
		len++;
	name = ft_calloc(len + 1, sizeof(char));
	if (!name)
		return (NULL);
	i = 0;
	while (i < len)
	{
		name[i] = var[i];
		i++;
	}
	return (name);
}

char	*copy_value_field(const char *var)
{
	int		len;
	char	*value;
	int		i;
	int		offset;

	len = ft_strlen(var);
	offset = 0;
	while (var[offset] != '=' && var[offset] != 0)
		offset++;
	if (offset == len)
		return (NULL);
	value = ft_calloc(len - offset + 1, sizeof(char));
	if (!value)
		return (NULL);
	offset++;
	i = 0;
	while (i + offset < len)
	{
		value[i] = var[i + offset];
		i++;
	}
	return (value);
}

static t_list	*new_env_node(const char *e_var)
{
	t_var	*var;
	t_list	*node;

	if (!e_var)
		return (NULL);
	var = ft_calloc(1, sizeof(*var));
	if (!var)
		return (NULL);
	var->name = copy_name_field(e_var);
	if (!var->name)
	{
		free_var(var);
		return (NULL);
	}
	var->value = copy_value_field(e_var);
	node = ft_lstnew(var);
	if (!node)
	{
		free_var(var);
		return (NULL);
	}
	return (node);
}

//takes env as a parameter and converts it into a list
t_list	*get_env_list(const char **env)
{
	t_list	*list_head;
	t_list	*temp_node;
	int		i;

	i = 1;
	list_head = new_env_node(env[0]);
	if (!list_head)
		return (NULL);
	temp_node = list_head;
	while (env[i])
	{
		temp_node->next = new_env_node(env[i]);
		if (!temp_node->next)
		{
			ft_lstclear(&list_head, free_var);
			return (NULL);
		}
		temp_node = temp_node->next;
		i++;
	}
	return (list_head);
}

char	**env_list_to_array(t_list *env_list)
{
	int		i;
	char	**array;
	t_var	*temp;

	if (!env_list)
		return (NULL);
	array = ft_calloc(ft_lstsize(env_list) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (env_list)
	{
		temp = env_list->content;
		if (temp->value)
			array[i] = ft_multistrjoin((char *[]){temp->name, \
			"='\"", temp->value, "\"", NULL});
		else
			array[i] = ft_strdup(temp->name);
		if (!array[i])
			env_list = ft_free_matrix((void ***)&array, i);
		if (env_list)
			env_list = env_list->next;
		i++;
	}
	return (array);
}
