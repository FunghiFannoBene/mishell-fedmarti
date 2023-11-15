/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:40:22 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/15 22:24:27 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len(char **args, bool flag)
{
	int		len;
	int		i;

	i = 1 + flag;
	len = 0;
	while (args[i] && args[i + 1])
	{
		len += ft_strlen(args[i]) + 1;
		i++;
	}
	len += ft_strlen(args[i]) + !flag + 1;
	return (len);
}

static int	no_args(int fd)
{
	write (fd, "\n", 1);
	return (0);
}

static int	ft_copy(char **args, bool flag, char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 1 + flag;
	while (args[i])
	{
		len += ft_strlcat(str, args[i], INT_MAX);
		if (args[i + 1])
			len += ft_strlcat(str, " ", len + 1);
		i++;
	}
	if (!flag)
		len += ft_strlcat(str, "\n", len + 1);
	return (len);
}

int	ft_echo(char **args, int fd)//da testare
{
	int		len;
	char	*str;
	bool	flag;

	str = NULL;
	if (!args[1])
		return (no_args(fd));
	flag = !ft_strncmp("-n", args[1], 3);
	len = 0;
	str = ft_calloc(get_len(args, flag) + 1, 1);
	if (!str)
		return (1);
	len = ft_copy(args, flag, str);
	write (fd, str, len);
	free(str);
	return (0);
}
