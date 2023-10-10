/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:24:03 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/11 01:14:25 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	is_(char c, char *charset)
{
	while (c && charset && *charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static inline char	*get_post_var(char *substr, t_var *var)
{
	if (!var)
	{
		while (!is_(*substr, NOT_VALID))
			substr++;
	}
	else
		substr += ft_strlen(var->name) + 1;
	return (ft_copy_up_to(substr, "$"));
}

static char	*expand_first_var(char *pre_var, char *substr, t_data *data)
{
	char	*post_var;
	char	*temp;
	char	**str_arr;
	t_var	*var;

	var = search_variable_tvar(substr, data);
	post_var = get_post_var(substr, var);
	if (!post_var)
		return (NULL);
	temp = pre_var;
	if (var)
		str_arr = (char *[]){pre_var, var->value, post_var, NULL};
	else
		str_arr = (char *[]){pre_var, post_var, NULL};
	pre_var = ft_multistrjoin(str_arr);
	free(temp);
	free(post_var);
	if (!pre_var)
		return (NULL);
	return (pre_var);
}

char	*expand_variables(char *str, t_data *data)
{
	char	*new_str;
	char	*substr;

	if (!str)
		return (NULL);
	substr = ft_strchr(str, '$');
	if (!substr)
		return (str);
	new_str = ft_copy_up_to(str, "$");
	if (!new_str)
		return (NULL);
	while (substr)
	{
		new_str = expand_first_var(new_str, substr, data);
		if (!new_str)
			return (NULL);
		substr = ft_strchr(new_str, '$');
	}
	free(str);
	return (new_str);
}
