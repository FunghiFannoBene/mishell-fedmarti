/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:12:01 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/04 20:38:09 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pwd_null(t_data *data)
{
	char	*pwd_path;

	pwd_path = getcwd(NULL, 0);
	getcwd(pwd_path, sizeof(*pwd_path));
	set_var_list("PWD", pwd_path, data->export_var);
	return (pwd_path);
}

int	ft_pwd(char	**args, t_data *data)
{
	t_var	*pwd;
	char	*pwd_path;
	char	*str;

	if (args[0] && args[1])
		return (!!write (2, "pwd: too many arguments\n", 25));
	pwd_path = NULL;
	pwd = get_var("PWD", data->export_var);
	if (pwd)
		pwd_path = ft_strdup(pwd->value);
	if (!pwd_path)
	{
		pwd_path = pwd_null(data);
		if (!pwd_path)
			return (1);
	}
	str = ft_strjoin(pwd_path, "\n");
	free(pwd_path);
	if (!str)
		return (1);
	write (1, str, ft_strlen(str));
	free(str);
	return (0);
}
