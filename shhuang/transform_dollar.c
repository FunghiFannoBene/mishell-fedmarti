/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 20:19:51 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/29 18:03:45 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../pipeline.h"
#include "short_code.h"

int	check_invalid(char c, char *invalid)
{
	int	i;

	i = 0;
	while (invalid[i])
	{
		if (invalid[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	checksymbol(char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (check_invalid(s[i], NOT_VALID) == 1)
			return (i + 1);
		i++;
	}
	return (i);
}

int	checksymbol2(char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (check_invalid(s[i], NOT_VALID) == 1)
			return (i + 1);
		i++;
	}
	return (i + 1);
}

void	init_slashes(t_slashes *s)
{
	s->i = 0;
	s->count = 0;
	s->x = 0;
	s->str = NULL;
}

void	run_count_slashes(char *tmp, t_slashes *s)
{
	while (tmp[s->i])
	{
		if (tmp[s->i] == '\'' || tmp[s->i] == '"')
			s->count++;
		s->i++;
	}
	s->i = 0;
}

char	*add_slashes(char *tmp)
{
	t_slashes	s;

	if (!tmp)
		return (NULL);
	init_slashes(&s);
	run_count_slashes(tmp, &s);
	if (s.count == 0)
		return (tmp);
	s.str = malloc(sizeof(char) * (ft_strlen(tmp) + s.count + 1));
	while (tmp[s.x])
	{
		if (tmp[s.x] == '\'' || tmp[s.x] == '"')
		{
			s.str[s.i] = '\\';
			s.i++;
		}
		s.str[s.i] = tmp[s.x];
		s.x++;
		s.i++;
	}
	s.str[s.i] = '\0';
	free(tmp);
	return (s.str);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*result;
	size_t	len;

	len = n;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	return ((char *)ft_memcpy(result, s, len));
}

void	init_replace(t_replace *r)
{
	r->env_len = 0;
	r->x = 0;
	r->str = NULL;
	r->result = NULL;
	r->start = NULL;
}

void	evaluate_free(char **tmp, char **s, t_replace *r)
{
	if (*tmp)
	{
		free(*tmp);
		*tmp = NULL;
	}
	free(r->start);
	free(*s);
	*s = NULL;
}

char	*replace_for_new_str(char *s, char *tmp, int i)
{
	t_replace	r;

	r.env_len = checksymbol2(s + i + 1);
	while (s[i])
	{
		if (s[i] == '$')
		{
			r.start = ft_strndup(s, i);
			if (tmp == NULL)
				r.result = ft_multistrjoin((char *[]){r.start, s + i
						+ r.env_len, NULL});
			else
				r.result = ft_multistrjoin((char *[]){r.start, "'", tmp, "'", s
						+ i + r.env_len, NULL});
			evaluate_free(&tmp, &s, &r);
			return (r.result);
		}
		i++;
	}
	return (s);
}

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
	if (s[d->i] == '\'')
		d->flag = 1;
	while (s[d->i] && d->flag == 1)
	{
		d->i++;
		if (s[d->i] == '\'')
			d->flag = 0;
	}
	d->start = d->i;
	return (1);
}

char	*transform_for_dollar(char *s, t_data *data)
{
	t_var			*list;
	t_short_dollar	d;

	init_transform_d(&d);
	while (s[++d.i] != '\0')
	{
		if (create_flags(s, &d) && s[d.i] == '\0')
			return (s);
		d.env_len = checksymbol(s + d.i + 1);
		if (s[d.i] == '$' && d.slash_count % 2 == 0 && d.env_len)
		{
			d.save = s[d.i + d.env_len];
			s[d.i + d.env_len] = '\0';
			list = search_variable_tvar(s + d.i, data);
			s[d.i + d.env_len] = d.save;
			if (list != NULL)
			{
				d.tmp = add_slashes(ft_strdup(list->value));
				d.size = ft_strlen(d.tmp);
				d.i += d.size + 1;
			}
			s = replace_for_new_str(s, d.tmp, d.start);
		}
	}
	return (s);
}
