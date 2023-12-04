/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:15:16 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/04 16:52:39 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

t_pnode	*get_head(t_pnode *node);

static inline int	command_not_found_error(char *name)
{
	char	*error_str;

	error_str = ft_multistrjoin((char *[]){"minishell: ", name, \
	": command not found\n", NULL});
	if (error_str)
	{
		write(2, error_str, ft_strlen(error_str));
		free(error_str);
	}
	return (127);
}

int	error_message(char *path, char *message)
{
	char	*msg;

	if (!message)
		return (1);
	if (path)
		msg = ft_multistrjoin((char *[]){"minishell: ", \
		path, ": ", message, "\n", NULL});
	else
		msg = ft_multistrjoin((char *[]){"minishell: ", message, "\n", NULL});
	if (!msg)
		return (1);
	write (2, msg, ft_strlen(msg));
	free(msg);
	return (0);
}

static int	is_executable(char *path)
{
	struct stat	statbuff;
	mode_t		file_type;

	stat(path, &statbuff);
	file_type = statbuff.st_mode & __S_IFMT;
	if (file_type == __S_IFREG)
	{
		if (access(path, X_OK))
			return (error_message(path, "Permission denied"));
		return (1);
	}
	else if (file_type == __S_IFDIR)
		return (error_message(path, "Is a directory"));
	return (0);
}

void	check_invalid_command(t_data *data, t_pnode *node, char *program_path)
{
	if (!program_path)
	{
		error_message(node->args[0], "command not found");
		ft_exit_pip(127, node, data);
	}
	if (access(program_path, F_OK))
	{
		error_message(program_path, "No such file or directory");
		ft_exit_pip(127, node, data);
	}
	if (!is_executable(program_path))
	{
		if (node->args[0] != program_path)
			free(program_path);
		ft_exit_pip(126, node, data);
	}
}

void	ft_exec(t_pnode *node, t_data *data)
{
	char	**env;
	char	*program_path;

	program_path = find_file_in_path(node->args[0], \
	get_var("PATH", data->export_var));
	check_invalid_command(data, node, program_path);
	env = env_list_to_array(data->export_var);
	if (!env)
		ft_exit_pip(1, node, data);
	execve(program_path, node->args, env);
	ft_free_matrix((void ***)&env, INT_MAX);
	free(program_path);
	ft_exit_pip(1, node, data);
}
