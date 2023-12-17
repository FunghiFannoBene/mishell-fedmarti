/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:04:49 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/17 13:48:02 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

int	create_flags(char *s, t_short_dollar *d)
{
	d->tmp = NULL;
	if (d->flag == 2 && s[d->i] == '"')
		d->flag = 0;
	else if (s[d->i] == '"')
		d->flag = 2;
	if (s[d->i] == '\'' && d->flag == 0)
		d->flag = 1;
	while (s[d->i] && d->flag == 1)
	{
		if (s[++d->i] == '\'')
		{
			d->flag = 0;
			break ;
		}
	}
	d->start = d->i;
	return (1);
}

char	*remove_spaces(char *str)
{
	int	length;

	length = ft_strlen(str);
	while (length > 0 && (str[length - 1] == ' '))
		length--;
	str[length] = '\0';
	return (str);
}

void	list_exist(t_var *list, t_short_dollar *d)
{
	if (list != NULL)
	{
		if(!list->value || list->value[0] == '\0')
			d->tmp = NULL;
		else
			d->tmp = add_slashes(ft_strdup(list->value));
		d->size = (int)ft_strlen(d->tmp);
	}
}

char	*remove_slashes(char *s)
{
	int		i;
	int		x;
	char	*new;

	i = 0;
	x = 0;
	new = ft_calloc((ft_strlen(s) + 1), 1);
	while (s[i])
	{
		if (s[i] != '\\')
			new[x++] = s[i];
		i++;
	}
	return (new);
}

char	*transform_for_dollar(char *s, t_data *data)
{
	t_var			*list;
	t_short_dollar	d;

	init_transform_d(&d, &s);
	while (s[++d.i] != '\0')
	{
		d.size = 0;
		if (create_flags(s, &d) && s[d.i] == '\0')
			return (s);
		if (s[d.i] == '$')
			d.env_len = checksymbol(s + d.i);
		if (s[d.i] == '$' && (d.env_len > 1
				|| ((s[d.i + 1] == '"' || s[d.i + 1] == '\'') && d.flag == 0)))
		{
			d.save = s[d.i + d.env_len];
			s[d.i + d.env_len] = '\0';
			list = search_variable_tvar(s + d.i, data);
			s[d.i + d.env_len] = (char)d.save;
			list_exist(list, &d);
			s = replace_for_new_str(s, d.tmp, d.start, &d.i);
			d.i += d.size;
		}
	}
	return (s);
}
