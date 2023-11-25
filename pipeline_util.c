/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:23:09 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/25 01:26:36 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"
#include "minishell.h"

void	free_data(t_data *data);

//closes fd1 if != 1 and fd2 if > 0
//if non-NULL frees the whole tree excluding node (starts from node->output)
//returns exit_status
int	on_return(int exit_status, t_pnode *node, int fd1, int fd2)
{
	if (fd1 != 1)
		close(fd1);
	if (fd2 > 0)
		close(fd2);
	if (node)
	{
		if (node->output && node->output->input[1])
			free(node->output->input[1]);
		free_tree(node->output);
		node->output = NULL;
	}
	return (exit_status);
}

void	ft_exit_pip(int exit_status, t_pnode *tree, t_data *data)
{
	free_data(data);
	free_tree(tree);
	exit(exit_status);
}
