/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:24:56 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/16 20:40:52 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

int	*command_exit_status_if_command(int *exit_status, t_pnode *command)
{
	if (command)
		return (&command->exit_status);
	return (exit_status);
}
