/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:01:33 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/25 17:02:07 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

int	is_builtin(char *str)
{
	int	len;

	if (!str || !ft_isalpha(*str))
		return (0);
	len = ft_strlen(str) + 1;
	if (len > 8 || len < 3)
		return (0);
	if (!ft_strncmp("echo", str, len))
		return (1);
	if (!ft_strncmp("env", str, len))
		return (1);
	if (!ft_strncmp("export", str, len))
		return (1);
	if (!ft_strncmp("exit", str, 5))
		return (1);
	if (!ft_strncmp("pwd", str, len))
		return (1);
	if (!ft_strncmp("cd", str, len))
		return (1);
	if (!ft_strncmp("unset", str, len))
		return (1);
	return (0);
}

int	ft_builtin(t_pnode *node, t_data *data)
{
	int	exit_status;

	exit_status = 0;
	if (!ft_strncmp("echo", node->args[0], 5))
		exit_status = (ft_echo(node->args, node->output_fd));
	else if (!ft_strncmp("env", node->args[0], 4))
		exit_status = (ft_env(data->export_var, node->output_fd));
	else if (!ft_strncmp("export", node->args[0], 7))
		exit_status = (ft_export(node->args, data, node->output_fd));
	else if (!ft_strncmp("exit", node->args[0], 5))
		exit_status = ft_exit(node->args, data, node);
	else if (!ft_strncmp("pwd", node->args[0], 4))
		return (ft_pwd(node->args, data));
	else if (!ft_strncmp("cd", node->args[0], 3))
		return (ft_cd(node->args, data));
	else if (!ft_strncmp("unset", node->args[0], 6))
		return (ft_unset(node->args, data));
	if (node->output_fd != 1)
		close(node->output_fd);
	return (exit_status);
}
