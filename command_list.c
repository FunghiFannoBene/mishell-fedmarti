/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:43:57 by shhuang           #+#    #+#             */
/*   Updated: 2023/12/14 02:43:57 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

char	**join_matrix_after_first(char **matrix1, char **matrix2)
{
	int		len1;
	int		len2;
	int		i;
	char	**result;

	len1 = matrix_length(matrix1);
	len2 = matrix_length(matrix2) - 1;
	result = malloc((len1 + len2 + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = copy_matrix(result, matrix1, 0, 0);
	if (i < 0)
	{
		free(result);
		return (NULL);
	}
	if (copy_matrix(result, matrix2, i, 1) < 0)
	{
		while (i > 0)
			free(result[--i]);
		free(result);
		return (NULL);
	}
	result[len1 + len2] = NULL;
	return (result);
}

void	try_add_after(t_pnode **actual, t_pnode **tmp)
{
	char		**save;

	while (*tmp && ((*tmp)->type == Redirect_input
			|| (*tmp)->type == Redirect_output
			|| (*tmp)->type == Redirect_input_heredoc
			|| (*tmp)->type == Redirect_output_append))
	{
		if ((*tmp)->args[0] && (*tmp)->args[1] != NULL)
		{
			save = (*actual)->args;
			(*actual)->args = join_matrix_after_first((*actual)->args,
					(*tmp)->args);
			free_matrix(&save);
		}
		*tmp = (*tmp)->output;
	}
	*actual = *tmp;
}

t_pnode	*join_struct_redirection(t_pnode **command)
{
	t_pnode		*actual;
	t_pnode		*tmp;

	tmp = *command;
	actual = *command;
	while (actual)
	{
		while (actual && actual->type != Program_Call)
			actual = actual->output;
		if (actual == NULL)
			break ;
		tmp = actual->output;
		if (tmp)
			try_add_after(&actual, &tmp);
		if (actual)
			actual = actual->output;
	}
	return (*command);
}

int	evaluate_command(char *start, int *i, t_cs *stat)
{
	while (start[*i] && start[*i] == ' ')
		(*i)++;
	if (start[*i] == '<' || start[*i] == '>')
		return (1);
	if (start[*i] == '|' || start[*i] == '\0')
		return (2);
	stat->start_c = *i;
	while (start[*i] && (start[*i] != '|' && start[*i] != '<'
			&& start[*i] != '>'))
		(*i)++;
	stat->end_c = *i;
	return (0);
}

t_pnode	*create_command_list(char *s)
{
	t_command	c;

	if (contains_only_one_virgoletta(s) || init_command(&c, s) == -1)
		return (NULL);
	sort_redirorder(s);
	while (1)
	{
		if (check_continuation(s, &c))
			break ;
		c.x = evaluate_next_struct(&c, s);
		if (c.x == -2)
			continue ;
		else if (c.x == 0)
			return (NULL);
		else if (c.x == 1)
			return (c.structure_head);
		command_to_structure(&c);
		structure_linking(&c);
		if (c.command_record == -1 || c.type == -2)
			break ;
	}
	c.structure_head = join_struct_redirection(&c.structure_head);
	return (c.structure_head);
}
