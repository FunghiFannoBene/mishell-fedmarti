/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:38:40 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/29 22:36:57 by shhuang          ###   ########.fr       */
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

t_var	*search_variable_tvar(char *str, t_data *data)
{
	t_var	*var;
	int		i;
	char	*name;

	if (!str)
		return (NULL);
	i = 0;
	if (*str != '$')
		str = ft_strchr(str, '$');
	str++;
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	i += (i == 0 && str[0] == '?');
	name = ft_calloc(i + 1, sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, i + 1);
	if (*name == '?')
		var = data->exit_status;
	else
		var = get_var(name, data->export_var);
	free(name);
	return (var);
}

//advances to the nearest $ and searches the subsequent sting within env_var
//return NULL if no match is found, the variable is NULL or malloc fails
//allocates a copy of the var variable value if found
char	*search_variable(char *str, t_data *data)
{
	t_var	*var;

	var = search_variable_tvar(str, data);
	if (!var || !var->value)
		return (NULL);
	return (ft_strdup(var->value));
}
