/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:57:32 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/15 23:01:05 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "minishell.h"

t_pnode	*get_boundary(t_pnode *node)
{
	while (node && node->type != Pipe)
		node = node->output;
	return (node);
}

int	change_fd(int prev_fd, int new_fd, char mode)
{
	if (mode != 'r' && mode != 'w')
		return (prev_fd);
	if ((prev_fd > 0 && mode == 'r') \
	|| (prev_fd > 1 && mode == 'w'))
		close (prev_fd);
	return (new_fd);
}

int	syntax_error(t_pnode *node)
{
	if (node->type == Pipe || (node->output && node->output->type == Pipe))
		write (2, "minishell: syntax error near unexpected token `|'\n", 50);
	else
		write(2, \
		"minishell: syntax error near unexpected token `newline'\n", 56);
	return (2);
}
