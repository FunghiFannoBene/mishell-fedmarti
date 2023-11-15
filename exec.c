/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:15:16 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/15 22:08:30 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

static inline int	command_not_found_error(char *name)
{
	char	*error_str;

	error_str = ft_strjoin(name, ": command not found\n");
	if (error_str)
	{
		write(2, error_str, ft_strlen(error_str));
		free(error_str);
	}
	return (127);
}

static int	_error_message(char *path, char *message)
{
	char	*msg;

	msg = ft_multistrjoin((char *[]){"minishell: ", \
	path, ": ", message, "\n", NULL});
	if (!msg)
		return (0);
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
			return (_error_message(path, "Permission denied"));
		return (1);
	}
	else if (file_type == __S_IFDIR)
		return (_error_message(path, "Is a directory"));
	return (0);
}

void	ft_exec(t_pnode *node, t_data *data)
{
	char	**env;
	char	*program_path;

	program_path = find_file_in_path(node->args[0], \
	get_var("PATH", data->export_var));
	if (!program_path)
		ft_exit_pip(command_not_found_error(node->args[0]), node, data);
	if (!is_executable(program_path))
	{
		if (node->args[0] != program_path)
			free(program_path);
		ft_exit_pip(126, node, data);
	}
	env = env_list_to_array(data->export_var);
	if (!env)
		ft_exit_pip(1, node, data);
	execve(program_path, node->args, env);
	ft_free_matrix((void ***)&env, INT_MAX);
	free(program_path);
	ft_exit_pip(1, node, data);
}
