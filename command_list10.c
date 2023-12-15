/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:54:06 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/14 11:10:37 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

int	slash_return(char *s, int *i, t_redirect **command)
{
	if (((*command)->flag == 0 || (*command)->flag == '"') && (s[*i] == '\\'
			&& (s[*i + 1] == '\'' || s[*i + 1] == '"')))
	{
		(*command)->size++;
		(*i) += 2;
		if (s[*i] == '\0')
		{
			(*command)->start += 1;
			return (0);
		}
		return (-1);
	}
	return (0);
}

int	found_virgoletta(char *n, t_us *u)
{
	if (u->s[u->i] == '\'' || u->s[u->i] == '"')
	{
		u->virgoletta = u->s[u->i];
		u->i++;
		while (u->s[u->i] && u->s[u->i] != u->virgoletta)
		{
			n[u->x] = u->s[u->i];
			u->i++;
			u->x++;
		}
		if (u->s[u->i] == '\0' || u->s[u->i] == ' '
			|| u->s[u->i] == '<' || u->s[u->i] == '>'
			|| u->s[u->i] == '|')
			return (1);
		u->i++;
		if (u->s[u->i] == '\0' || u->s[u->i] == ' '
			|| u->s[u->i] == '<' || u->s[u->i] == '>'
			|| u->s[u->i] == '|')
			return (1);
	}
	return (0);
}

int	matrix_length(char **matrix)
{
	int	length;

	length = 0;
	while (matrix[length] != NULL)
		length++;
	return (length);
}

int	copy_matrix(char **dest, char **src, int start, int skip_first)
{
	int	i;
	int	j;

	i = start;
	j = skip_first;
	while (src[j] != NULL)
	{
		dest[i] = ft_strdup(src[j]);
		if (!dest[i])
		{
			while (i > start)
				free(dest[--i]);
			return (-1);
		}
		i++;
		j++;
	}
	return (i);
}

void	free_matrix(char ***matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL || *matrix == NULL)
		return ;
	while ((*matrix)[i] != NULL)
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}
