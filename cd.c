/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 00:08:54 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/04 01:06:41 by fedmarti         ###   ########.fr       */
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
	path = ft_strjoin(home->value, args[1]);
	return (path);
}

static void	failed_cd_message(char *path)
{
	char	*message;
	char	*temp;

	message = ft_strjoin("cd: ", path);
	if (!message)
		return ;
	temp = message;
	message = ft_strjoin(message, ": No such file or directory\n");
	free(temp);
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
		pwd->value = ft_strdup(getenv("PWD"));
	}
}

int	cd(char **args, t_data *data)
{
	char	*path;
	int		return_val;

	path = args[1];
	if (args[2])
	{
		write (2, "cd: too many arguments", 23);
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
		failed_cd_message(path);
	if (!args[1] || ft_strncmp(args[1], path, ft_strlen(args[1])))
		free(path);
	update_pwd(data);
	return (return_val);
}
