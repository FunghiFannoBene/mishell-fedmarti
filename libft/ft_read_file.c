/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:39:51 by fedmarti          #+#    #+#             */
/*   Updated: 2023/12/05 23:15:16 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static t_list	*read_into_list(int fd)
{
	char	*line;
	t_list	*temp;
	t_list	*list;

	line = get_next_line(fd);
	list = NULL;
	while (line)
	{
		temp = ft_lstnew(line);
		if (!temp)
			break ;
		ft_lstadd_back(&list, temp);
		line = get_next_line(fd);
	}
	return (list);
}

char	**ft_read_file(char *path)
{
	char	**file;
	int		fd;
	t_list	*list;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
		return (NULL);
	list = read_into_list(fd);
	close(fd);
	if (!list)
		return (NULL);
	file = (char **)ft_lst_to_matrix(list);
	return (file);
}
