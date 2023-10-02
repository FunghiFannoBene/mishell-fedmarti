/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:56:17 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/02 01:57:19 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_name_field(const char *var); //included here not to bloat the header
char	*copy_value_field(const char *var);
int		print_export(t_list *export_vars);

int	export(char **args, t_data *data)
{
	int		i;
	t_var	temp;

	if (!args[1])
		return (print_export(data->export_var));
	i = 0;
	while (args[i])
	{
		temp = (t_var){copy_name_field(args[i]), copy_value_field(args[i])};
		if (!temp.name)
		{
			if (temp.value)
				free (temp.value);
			return (1);
		}
		set_var_list(temp.name, temp.value, data->export_var);
		free(temp.name);
		if (temp.value)
			free(temp.value);
		i++;
	}
	return (0);
}
