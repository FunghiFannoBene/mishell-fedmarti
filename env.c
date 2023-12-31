/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:02:28 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/25 16:57:06 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_to_str(t_var *var)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	if (!var || !var->name)
		return (NULL);
	if (!var->value)
		return (ft_strdup(var->name));
	len = ft_strlen(var->name) + ft_strlen(var->value) + 1;
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (var->name[i])
	{
		str[i] = var->name[i];
		i++;
	}
	str[i++] = '=';
	j = 0;
	while (var->value[j])
		str[i++] = var->value[j++];
	return (str);
}

char	**env_list_to_matrix(t_list *env_list)
{
	int		i;
	char	**new_env;

	new_env = ft_calloc(ft_lstsize(env_list) + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env_list)
	{
		if (((t_var *)env_list->content)->value != NULL)
		{
			new_env[i] = var_to_str(env_list->content);
			i++;
		}
		if (i && !new_env)
		{
			ft_free_matrix((void ***)&new_env, i);
			break ;
		}
		env_list = env_list->next;
	}
	return (new_env);
}

int	ft_env(t_list	*env_list, int fd)
{
	char	*str_var;
	char	*temp;

	while (env_list)
	{
		if (((t_var *)env_list->content)->value != NULL)
		{
			temp = var_to_str(env_list->content);
			if (!temp)
				return (1);
			str_var = ft_strjoin(temp, "\n");
			if (!str_var)
			{
				free (temp);
				return (1);
			}
			write (fd, str_var, ft_strlen(str_var));
			free (temp);
			free (str_var);
		}
		env_list = env_list->next;
	}
	return (0);
}
