/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list9.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:33:41 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/14 19:06:25 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*joint;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1) + ft_strlen(s2);
	joint = (char *)ft_calloc((len + 1), sizeof(char));
	if (!joint)
		return (NULL);
	i = 0;
	while (len-- && *s1)
	{
		joint[i] = *s1;
		s1++;
		i++;
	}
	len++;
	while (len-- && *s2)
	{
		joint[i] = *s2;
		s2++;
		i++;
	}
	joint[i] = 0;
	return (joint);
}

void	set_status(char *s, int i, int *status)
{
	if (s[i] == ' ' || s[i] == '\0')
		*status = 0;
	else
		*status = 1;
}

void	structure_linking(t_command *c)
{
	t_pnode	*prev;

	if (c->structure_actual == NULL)
		c->structure_actual = c->structure_head;
	else
	{
		prev = c->structure_actual;
		prev->output = c->structure;
		c->structure->input = prev;
		c->structure_actual = c->structure_actual->output;
	}
}

int	is_void(t_command *c)
{
	if (c->structure->type == Null && !c->structure_head)
	{
		free(c->structure);
		return (1);
	}
	return (0);
}

void	free_tmp_new_head(t_command **c)
{
	free((*c)->head->str);
	(*c)->temp = (*c)->head;
	(*c)->head = (*c)->head->next;
	free((*c)->temp);
}
