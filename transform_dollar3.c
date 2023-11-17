/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dollar3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:39:48 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/17 07:59:33 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

char	*add_slashes(char *tmp)
{
	t_slashes	s;

	if (!tmp)
		return (NULL);
	init_slashes(&s);
	run_count_slashes(tmp, &s);
	if (s.count == 0)
		return (tmp);
	s.str = malloc(sizeof(char) * (size_t)(ft_strlen(tmp) + (size_t)s.count + 1));
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

char	*replace_for_new_str(char *s, char *tmp, int i, int *di)
{
	t_replace	r;

	r.env_len = checksymbol2(s + i + 1);
	while (s[i])
	{
		if (s[i] == '$')
		{
			r.start = ft_strndup(s, (size_t)i);
			if (tmp == NULL)
			{
				(*di)=i-1;
				r.result = ft_multistrjoin((char *[]){r.start, s + i
						+ r.env_len, NULL});
			}
			else
			{
				(*di)=i;
				r.result = check_and_addx(r.start, tmp, s+i+r.env_len, di);
			}
			evaluate_free(&tmp, &s, &r);
			return (r.result);
		}
		i++;
	}
	return (s);
}
