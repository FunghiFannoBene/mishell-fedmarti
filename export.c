/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:56:17 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/29 19:40:52 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_name_field(const char *var);
char	*copy_value_field(const char *var);
int		print_export(t_list *export_vars, int fd);

static inline int	wrong_character_error(char *str)
{
	char	*error_message;

	error_message = ft_multistrjoin((char *[]){"minishell: export: `", \
	str, "\': not a valid identifier\n", NULL});
	if (!error_message)
		return (1);
	write (2, error_message, ft_strlen(error_message));
	free (error_message);
	return (1);
}

static inline int	malloc_failure(char *str)
{
	if (str)
		free(str);
	return (1);
}

//adds temp to list
//checks if the list is null and if so creates a head node
static inline int	export_variable(t_var temp, t_data *data)
{
	t_var	*var;

	if (data->export_var)
		set_var_list(temp.name, temp.value, data->export_var);
	else
		var = new_var(temp.name, temp.value);
	free(temp.name);
	if (temp.value)
		free(temp.value);
	if (data->export_var)
		return (1);
	else if (!var)
		return (0);
	data->export_var = ft_lstnew(var);
	if (!data->export_var)
	{
		free_var(var);
		return (0);
	}
	return (1);
}

int	ft_export(char **args, t_data *data, int fd)
{
	int		i;
	t_var	temp;
	int		return_val;

	if (!args[1])
		return (print_export(data->export_var, fd));
	i = 0;
	return_val = 0;
	while (args[++i])
	{
		temp = (t_var){copy_name_field(args[i]), copy_value_field(args[i])};
		if (!temp.name)
			return (malloc_failure(temp.value));
		if (!is_name_valid(temp.name))
		{
			return_val = wrong_character_error(temp.name);
			free(temp.name);
			if (temp.value)
				free(temp.value);
		}
		else if (!export_variable(temp, data))
			return (1);
	}
	return (return_val);
}
