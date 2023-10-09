/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:24:03 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/09 18:59:01 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	is_(char c, char *charset)
{
	while (charset && *charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

//advances to the nearest $ and searches the subsequent sting within env_var
//return NULL if no match is found, the variable is NULL or malloc fails
//allocates a copy of the var variable value if found
char	*search_variable(char *str, t_data *data)
{
	t_var	*var;
	int		i;
	char	*name;

	if (!str)
		return (NULL);
	i = 0;
	while (*str != 0 && *str != '$')
		str++;
	while (str[i] && !is_(str[i], "!@#$%^*=+~,.;: "))
		i++;
	name = ft_calloc(i + 1, sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, i);
	if (*name == '?')
		var = data->exit_status;
	else
		var = get_var(name, data->export_var);
	free(name);
	if (!var || !var->value)
		return (NULL);
	return (ft_strdup(var->value));
}

static inline void	get_post_var(char *str, char *dest)
{
	while (!is_(*str, "!@#$%^*=+~,.;: "))
			str++;
	ft_strlcpy(dest, str, INT_MAX);
}

char	*expand_variables(char *str, t_data *data)
{
	char	pre_var[256];
	char	post_var[256];
	char	*temp;
	char	*var_content;

	if (!str)
		return (NULL);
	temp = ft_strchr(str, '$');
	ft_strlcpy(pre_var, str, str - temp);
	while (*temp)
	{
		get_post_var(temp, post_var);
		var_content = search_variable(temp, data);
		ft_strlcat(pre_var, var_content, 255);
		ft_strlcat(pre_var, post_var, 255);
		if (var_content)
			free(var_content);
		temp = ft_strchr(pre_var, '$');
	}
	free(str);
	return (ft_strdup(pre_var));
}
