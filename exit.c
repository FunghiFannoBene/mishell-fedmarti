/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:17:08 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/15 20:10:16 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data);

static int	is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	bad_argument(char *arg)
{
	char	*err_msg;

	err_msg = ft_multistrjoin((char *[]){"bash: exit: ", \
	arg, ": numeric argument required\n", NULL});
	if (!err_msg)
		return ;
	write (2, err_msg, ft_strlen(err_msg));
	free(err_msg);
}

int	ft_exit(char **args, t_data *data)
{
	if (!args[1])
	{
		free_data(data);
		exit (0);
	}
	if (!is_number(args[1]))
	{
		bad_argument(args[1]);
		free_data(data);
		exit (2);
	}
	if (args[2])
	{
		write (2, "bash: exit: too many arguments\n", 31);
		return (1);
	}
	return (0);
}