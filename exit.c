/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:17:08 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/04 17:50:51 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

void	free_data(t_data *data);

static int	is_number(char *str)
{
	while (*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		str++;
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

	err_msg = ft_multistrjoin((char *[]){"minishell: exit: ", \
	arg, ": numeric argument required\n", NULL});
	if (!err_msg)
		return ;
	write (2, err_msg, ft_strlen(err_msg));
	free(err_msg);
}

int	ft_exit(char **args, t_data *data, t_pnode *node)
{
	int	exitno;

	if (args[1] && args[2])
	{
		write (2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	if (!args[1])
		exitno = 0;
	else if (is_number(args[1]))
		exitno = ft_atoi(args[1]);
	else
	{
		bad_argument(args[1]);
		exitno = 2;
	}
	if (node)
		free_node(node);
	free_data(data);
	exit(exitno);
	return (0);
}
