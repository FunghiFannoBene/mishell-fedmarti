/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:41:15 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/15 21:08:39 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum	e_access_type{
	Nonexistent,
	Accessible,
	Direcory,
	Perm_denied
};

int	is_file_in_dir(char *name, DIR *dir)
{
	struct dirent	*dirent_;
	int				name_len;

	name_len = ft_strlen(name) + 1;
	dirent_ = readdir(dir);
	while (dirent_)
	{
		if (!ft_strncmp(name, dirent_->d_name, name_len))
			return (1);
		dirent_ = readdir(dir);
	}
	return (0);
}

char	*find_file_in_path(char *name, t_var *env_v_path)
{
	char	*path;
	char	**env_paths;
	int		i;
	DIR		*dir;

	if (!name || name[0] == '/' || (name[0] == '.' && name[1] == '/'))
		return (name);
	if (!env_v_path || !env_v_path->value)
		return (ft_strjoin("./", name));
	env_paths = ft_split(env_v_path->value, ':');
	if (!env_paths)
		return (name);
	i = -1;
	path = NULL;
	while (env_paths[++i] && !path)
	{
		dir = opendir(env_paths[i]);
		if (!dir)
			continue ;
		if (is_file_in_dir(name, dir))
			path = ft_multistrjoin((char *[]){env_paths[i], "/", name, NULL});
		closedir(dir);
	}
	ft_free_matrix((void ***)&env_paths, INT_MAX);
	return (path);
}
