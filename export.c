/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:56:17 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/04 23:50:11 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_name_field(const char *var); //included here not to bloat the header
char	*copy_value_field(const char *var);
int		print_export(t_list *export_vars);

static void	wrong_character_error(char *str)
{
	char	*error_message;

	error_message = ft_multistrjoin((char *[]){"bash: export: `", \
	str, "\': not a valid identifier\n", NULL});
	if (!error_message)
		return ;
	write (2, error_message, ft_strlen(error_message));
	free (error_message);
}

static inline int	malloc_failure(char *str)
{
	if (str)
		free(str);
	return (1);
}

int	ft_export(char **args, t_list *export_var_list)
{
	int		i;
	t_var	temp;
	int		return_val;

	if (!args[1]) //e' come dire argv == 1
		return (print_export(export_var_list));
	i = 0;
	return_val = 0;
	while (args[++i])
	{
		temp = (t_var){copy_name_field(args[i]), copy_value_field(args[i])};
		if (!temp.name)
			return (malloc_failure(temp.value));
		if (ft_strhas(temp.name, "!@#$%^*=+~,.;:"))
		{
			return_val = 1;
			wrong_character_error(temp.name);
		}
		else
			set_var_list(temp.name, temp.value, export_var_list);
		free(temp.name);
		if (temp.value)
			free(temp.value);
	}
	return (return_val);
}
