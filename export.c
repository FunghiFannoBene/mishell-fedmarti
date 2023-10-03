/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:56:17 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/03 20:13:49 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_name_field(const char *var); //included here not to bloat the header
char	*copy_value_field(const char *var);
int		print_export(t_list *export_vars);

int	ft_export(char **args, t_list *export_var_list)
{
	int		i;
	t_var	temp;

	if (!args[1]) //e' come dire argv == 1
		return (print_export(export_var_list));
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
		set_var_list(temp.name, temp.value, export_var_list);
		free(temp.name);
		if (temp.value)
			free(temp.value);
		i++;
	}
	return (0);
}
