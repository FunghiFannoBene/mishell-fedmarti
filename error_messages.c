/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:11:07 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/05 20:46:22 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	no_such_file_or_directory(char *filename)
{
	char	*error_str;

	error_str = ft_multistrjoin((char *[]){"minishell: ", filename, \
	": No such file or directory\n", NULL});
	if (error_str)
	{
		write (2, error_str, ft_strlen(error_str));
		free(error_str);
	}
	return (1);
}
