/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <shhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:41:17 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/31 15:07:57 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../pipeline.h"
#include "short_code.h"

void	assign_redirection(int x, t_pnode *structure)
{
	if (x == 1)
		structure->type = Redirect_input;
	else if (x == 2)
		structure->type = Redirect_input_heredoc;
	else if (x == 3)
		structure->type = Redirect_output;
	else if (x == 4)
		structure->type = Redirect_output_append;
}

void	check_redirect_init(int *x, int *flag, int *count, t_pnode **structure)
{
	*count = 0;
	*flag = 0;
	*x = 0;
	(*structure)->type = Null;
}

int	check_redirect(char *s, int *i, t_pnode *structure)
{
	int	x;
	int	flag;
	int	count;

	check_redirect_init(&x, &flag, &count, &structure);
	if (s[*i] == '>' || s[*i] == '<')
	{
		flag = s[*i];
		if (s[*i] == '>')
		{
			x += 2;
		}
		while (s[*i] && s[*i] == flag)
		{
			(*i)++;
			x++;
			if (++count == 2)
				break ;
		}
		assign_redirection(x, structure);
		if (s[*i] == flag)
			return (1);
	}
	return (0);
}

int	check_pipe(char *s, int *i, t_pnode *structure)
{
	if (s[*i] == '|')
	{
		structure->type = Pipe;
		structure->args = NULL;
		(*i)++;
		return (1);
	}
	return (0);
}

int	check_virgolette_dispari(char *s, int *i)
{
	int	count_double;
	int	count_single;
	int	x;

	x = *i;
	count_single = 0;
	count_double = 0;
	while (s[x])
	{
		if (s[x] == '\'' && !(s[x] == '\\' && s[x + 1] == '\''))
			count_single++;
		else if (s[x] == '"' && !(s[x] == '\\' && s[x + 1] == '"'))
			count_double++;
		x++;
	}
	if (count_double % 2 || count_single % 2)
		return (-1);
	return (0);
}
