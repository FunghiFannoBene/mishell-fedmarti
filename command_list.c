/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:18:44 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/25 15:18:44 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "short_code.h"

char	**join_matrix_after_first(char **matrix1, char **matrix2)
{
	int		len1;
	int		len2;
	int		i;
	char	**result;
	int		j;

	len1 = 0;
	len2 = -1;
	i = 0;
	while (matrix1[len1] != NULL)
		len1++;
	while (matrix2[len2 + 1] != NULL)
		len2++;
	result = malloc((len1 + len2 + 1) * sizeof(char *));
	while (matrix1[i] != NULL)
	{
		result[i] = strdup(matrix1[i]);
		if (!result[i])
		{
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	j = 1;
	while (matrix2[j] != NULL)
	{
		result[i + j - 1] = strdup(matrix2[j]);
		if (!result[i + j - 1])
		{
			while (j > 1)
				free(result[i + --j - 1]);
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		j++;
	}
	result[len1 + len2] = NULL;
	return (result);
}

void	free_matrix(char ***matrix)
{
	int i;

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

t_pnode	*join_struct_redirection(t_pnode **command)
{
	t_pnode *actual;
	t_pnode *tmp;
	char **save;
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
		{
			while (tmp && (tmp->type == Redirect_input
					|| tmp->type == Redirect_output
					|| tmp->type == Redirect_input_heredoc
					|| tmp->type == Redirect_output_append))
			{
				if (tmp->args[0] && tmp->args[1] != NULL)
				{
					save = actual->args;
					actual->args = join_matrix_after_first(actual->args,
							tmp->args);
					tmp->args[1] = NULL;
					free_matrix(&save);
				}
				tmp = tmp->output;
			}
			actual = tmp;
		}
		if (actual)
			actual = actual->output;
	}
	return (*command);
}

t_pnode	*create_command_list(char *s)
{
	t_command c;

	if (contains_only_one_virgoletta(s) || init_command(&c, s) == -1)
		return (NULL);
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
