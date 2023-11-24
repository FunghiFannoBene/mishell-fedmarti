/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 20:19:51 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/17 07:56:12 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

void	init_transform_d(t_short_dollar *d)
{
	d->tmp = NULL;
	d->i = -1;
	d->env_len = 0;
	d->save = 0;
	d->save_pre = 0;
	d->size = 0;
	d->slash_count = 0;
	d->start = 0;
	d->flag = 0;
}

int	create_flags(char *s, t_short_dollar *d)
{
	d->tmp = NULL;
	if (s[d->i] == '\\')
	{
		while (s[d->i] == '\\')
		{
			d->slash_count++;
			d->i++;
		}
	}
	else
		d->slash_count = 0;
	if((check_virgolette_doppie(s, d->i) == 0))
	{
		if (s[d->i] == '\'')
			d->flag = 1;
		while (s[d->i] && d->flag == 1)
		{
			d->i++;
			if (s[d->i] == '\'')
				d->flag = 0;
		}
	}
	d->start = d->i;
	return (1);
}

void remove_spaces(char *str) 
{
    int length = ft_strlen(str);
    
    while (length > 0 && str[length - 1] == ' ')
        length--;

    str[length] = '\0';
}

char	*transform_for_dollar(char *s, t_data *data)
{
	t_var			*list;
	t_short_dollar	d;

	init_transform_d(&d);
	while (s[++d.i] != '\0')
	{
		d.size = 0;
		if (create_flags(s, &d) && s[d.i] == '\0')
			return (s);
		d.env_len = checksymbol(s + d.i + 1);
		if (s[d.i] == '$' && d.slash_count % 2 == 0 && d.env_len)
		{
			d.save = s[d.i + d.env_len + 1];
			s[d.i + d.env_len + 1] = '\0';
			list = search_variable_tvar(s + d.i, data);
			s[d.i + d.env_len + 1] = (char)d.save;
			if (list != NULL)
			{
				d.tmp = add_slashes(ft_strdup(list->value));
				d.size = (int)ft_strlen(d.tmp);
			}
			s = replace_for_new_str(s, d.tmp, d.start, &d.i);
			d.i+=d.size;
		}
	}
	remove_spaces(s);
	return (s);
}
