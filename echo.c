/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:40:22 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/06 17:42:16 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_flag(char *str)
{
	if (!str || ft_strncmp(str, "-n", 2))
		return (0);
	str += 2;
	while (*str == 'n')
		str++;
	return (!*str);
}

static int	get_first_arg(char **args, bool flag)
{
	int	i;

	i = 1;
	if (!flag)
		return (i);
	while (is_flag(args[i]))
		i++;
	return (i);
}

static int	get_len(char **args, bool flag)
{
	int		len;
	int		i;

	len = 0;
	i = get_first_arg(args, flag);
	while (args[i] && args[i + 1])
	{
		len += ft_strlen(args[i]) + 1;
		i++;
	}
	len += ft_strlen(args[i]) + !flag + 1;
	return (len);
}

static int	ft_copy(char **args, bool flag, char *str)
{
	int	len;
	int	i;

	len = 0;
	i = get_first_arg(args, flag);
	while (args[i])
	{
		len += ft_strlcpy(str + len, args[i], INT_MAX);
		if (args[i + 1])
			len += ft_strlcpy(str + len, " ", 2);
		i++;
	}
	if (!flag)
		len += ft_strlcpy(str + len, "\n", 2);
	return (len);
}

int	ft_echo(char **args, int fd)
{
	int		len;
	char	*str;
	bool	flag;

	str = NULL;
	if (!args[1])
	{
		write (fd, "\n", 1);
		return (0);
	}
	flag = is_flag(args[1]);
	len = 0;
	str = ft_calloc(get_len(args, flag) + 1, 1);
	if (!str)
		return (1);
	len = ft_copy(args, flag, str);
	write (fd, str, len);
	free(str);
	return (0);
}
