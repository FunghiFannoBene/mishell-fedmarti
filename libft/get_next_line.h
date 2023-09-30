/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:12:45 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/20 15:35:28 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

char	*get_next_line(int fd);
int		check(char *str);
void	*f_calloc(size_t nmemb, size_t size);
char	*f_strjoin(char *s1, char *s2);
void	ft_reset(char **p);

#endif
