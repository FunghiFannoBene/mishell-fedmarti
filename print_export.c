/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 01:56:48 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/02 02:06:33 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_name_field(const char *var); //included here not to bloat the header
char	*copy_value_field(const char *var);

static void	arr_insert(t_var *var, t_var **array, int pos)
{
	int	i;

	i = pos;
	while (array[i + 1])
		i++;
	while (i > pos)
	{
		array[i] = array[i - 1];
		i--;
	}
	array[pos] = var;
}

static void	add_alphabetical_order(t_var *var, t_var **array, int var_count)//still untested
{
	int	name_len;
	int	n;
	int	size;

	if (var_count == 0)
	{
		array[0] = var;
		return ;
	}
	name_len = ft_strlen(var->name);
	n = size >> 1;
	size = var_count;
	while (size > 1)
	{
		size >>= 1;
		if (ft_strncmp(var->name, array[n]->name, name_len) < 0)
			n -= size;
		else
			n += size;
	}
	if (ft_strncmp(var->name, array[n]->name, name_len) > 0)
		n++;
	arr_insert(var, array, n);
}
 
static t_var	**extract_arr(t_list *export_list)
{
	t_var	**arr;
	t_var	*temp;
	int		i;

	if (!export_list)
		return (NULL);
	arr = ft_calloc(ft_lstsize(export_list) + 1, sizeof(*t_var));
	if (!arr)
		return (NULL);
	i = 0;
	while (export_list)
	{
		temp = export_list->content;
		add_alphabetical_order(temp, arr, i);
		i++;
		export_list = export_list->next;
	}
	return (arr);
}

static char	*export_var_str(t_var *var)
{
	char	*str;
	char	*temp;

	if (!var->value)
		return (ft_strdup(var->name));
	temp = ft_strjoin(var->name, "=\"");
	if (!temp)
		return (NULL);
	str = ft_strjoin(temp, var->value);
	free (temp);
	if (!str)
		return (NULL);
	temp = str;
	str = ft_strjoin(temp, "\"\n");
	free(temp);
	return (str);
}

int	print_export(t_list *export_vars)
{
	t_var	**var_arr;
	char	*var_str;
	int		i;
	
	var_arr = extract_arr(export_vars);
	if (!var_arr)
		return (export_vars != NULL); //if the list is empty this is normal, othewise malloc failed
	i = 0;
	while (var_arr[i])
	{
		var_str = export_var_str(var_arr[i]);
		if (!var_str)
			return (1);
		write (1, var_str, ft_strlen(var_str));
		free (var_str);
		i++;
	}
	free(var_arr);
	return (0);
}