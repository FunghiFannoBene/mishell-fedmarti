/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 00:08:54 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/04 17:37:28 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*using_home(char **args, t_data *data)
{
	char	*path;
	t_var	*home;

	home = get_var("HOME", data->export_var);
	if (!home)
		return (NULL);
	if (!args[1])
		return (ft_strdup(home->value));
	path = ft_strjoin(home->value, &args[1][1]);
	return (path);
}

static char	*err_msg(char *path, char *msg)
{
	return (ft_multistrjoin((char *[]){"minishell: cd: ", \
		path, ": ", msg, "\n", NULL}));
}

static void	failed_cd_message(char *path, int *exit_status)
{
	char		*message;
	struct stat	statbuff;

	message = NULL;
	*exit_status = 1;
	if (access(path, F_OK))
	{
		message = err_msg(path, "No such file or directory");
		*exit_status = 1;
	}
	else if (!stat(path, &statbuff) \
	&& (statbuff.st_mode & __S_IFMT) != __S_IFDIR)
	{
		message = err_msg(path, "Not a directory");
		*exit_status = 1;
	}
	else if (access(path, X_OK))
	{
		message = err_msg(path, "Permission denied");
		*exit_status = 1;
	}
	if (!message)
		return ;
	write (2, message, ft_strlen(message));
	free(message);
}

static void	update_pwd(t_data *data)
{
	t_var	*pwd;
	t_var	*old_pwd;

	pwd = get_var("PWD", data->export_var);
	old_pwd = get_var("OLDPWD", data->export_var);
	if (old_pwd)
	{
		if (old_pwd->value)
			free(old_pwd->value);
		if (pwd && pwd->value)
		{
			old_pwd->value = pwd->value;
			pwd->value = NULL;
		}
	}
	if (pwd)
	{
		if (pwd->value)
			free(pwd->value);
		pwd->value = getcwd(NULL, 0);
		getcwd(pwd->value, sizeof(*pwd->value));
	}
}

int	ft_cd(char **args, t_data *data)
{
	char	*path;
	int		return_val;

	path = args[1];
	if (args[1] && args[2])
	{
		write (2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (!args[1] || args[1][0] == '~')
	{
		path = using_home(args, data);
		if (!path)
		{
			write (2, "cd: HOME not set\n", 18);
			return (1);
		}
	}
	return_val = chdir(path);
	if (return_val)
		failed_cd_message(path, &return_val);
	if (!args[1] || ft_strncmp(args[1], path, ft_strlen(args[1])))
		free(path);
	update_pwd(data);
	return (return_val);
}
