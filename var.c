/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 18:51:03 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/30 23:52:11 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//allocates a t_var
//duplicates name and value (they're NOT free'd)
//if name is null the var is not allocated, var can be null though
//returns NULL on failure
t_var	*new_var(char *name, char *value)
{
	t_var	*var;

	if (!name)
		return (NULL);
	var = ft_calloc(1, sizeof(*var));
	if (!var)
		return (NULL);
	var->name = ft_strdup(name);
	if (!var->name)
	{
		free(var);
		return (NULL);
	}
	var->value = ft_strdup(value);
	if (!var->value)
	{
		free (var->name);
		free (var);
		return (NULL);
	}
	return (var);
}

//pretty self explanatory
void	free_var(void *variable)
{
	t_var	*var;

	var = variable;
	if (!var)
		return ;
	if (var->value)
		free(var->value);
	if (var->name)
		free(var->name);
	free(var);
}

//iterates through a list of type t_var comparing the name with "name"
//if it matches it returns a pointer to the variable
//it returns null if the variable doesn't exist
t_var	*get_var(char *name, t_list *list)
{
	t_var	*content;
	size_t	name_len;

	if (!name)
		return (NULL);
	name_len = ft_strlen(name) + 1;
	while (list)
	{
		content = list->content;
		if (content && !ft_strncmp(name, content->name, name_len))
			return (content);
		list = list->next;
	}
	return (NULL);
}

//copies new_value into var
//return value : 0 on success. 1 on error
int	set_var(t_var *var, char *new_value)
{
	if (!var)
		return (1);
	if (var->value)
		free(var->value);
	var->value = ft_strdup(new_value);
	return (var->value != NULL);
}

//changes value of variable if it exists, creates new one if it doesn't
//does NOT free the arguments name or value
//return value : 0 on success. 1 on error
int	set_var_list(char *name, char *value, t_list *list)
{
	t_var	*var;
	size_t	name_len;

	if (!name)
		return (1);
	name_len = ft_strlen(name) + 1;
	while (1)//cycle breaks from the ifs
	{
		var = list->content;
		if (var && !ft_strncmp(name, var->name, name_len))
			return (set_var(var, value));
		else if (!list->next)
			break ;
		list = list->next;
	}
	var = new_var(name, value);
	if (!var)
		return (1);
	list->next = ft_lstnew(var);
	if (!list->next)
	{
		free_var(var);
		return (1);
	}
	return (0);
}
