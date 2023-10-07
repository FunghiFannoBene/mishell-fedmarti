/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:35:12 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/07 22:56:24 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	null_args(void)
{
	write(2, "bash: syntax error near unexpected token `newline\'", 51);
	return (2);
}

int	ft_heredoc(char **args, int fd)
{
	int		eof_len;
	char	*input;
	char	*output_str;
	char	*temp;

	if (!*args)
		return (null_args());
	eof_len = ft_strlen(*args) + 1;
	output_str = ft_calloc(1, sizeof(char));
	if (!output_str)
		return (1);
	input = readline(">");
	while (input && ft_strncmp(input, *args, eof_len))
	{
		temp = output_str;
		output_str = ft_multistrjoin((char *[]){output_str, input, "\n", NULL});
		free(input);
		free(temp);
		if (!output_str)
			return (1);
		input = readline(">");
	}
	write (fd, output_str, ft_strlen(output_str));
	free(output_str);
	return (0);
}
