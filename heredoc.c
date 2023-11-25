/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:35:12 by fedmarti          #+#    #+#             */
/*   Updated: 2023/11/25 16:57:41 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	null_args(void)
{
	write(2, "bash: syntax error near unexpected token `newline\'", 51);
	return (2);
}

static inline char	*coumpound_input(char *str, char *input, t_data *data)
{
	char	*temp;

	input = expand_variables(input, data);
	if (!input)
		return (NULL);
	temp = str;
	str = ft_multistrjoin((char *[]){str, input, "\n", NULL});
	free(input);
	free(temp);
	return (str);
}

int	ft_heredoc(char **args, int fd, t_data *data)
{
	int		eof_len;
	char	*input;
	char	*output_str;

	if (!*args)
		return (null_args());
	eof_len = ft_strlen(*args) + 1;
	output_str = ft_calloc(1, sizeof(char));
	if (!output_str)
		return (1);
	input = readline(">");
	while (input && ft_strncmp(input, *args, eof_len))
	{
		output_str = coumpound_input(output_str, input, data);
		if (!output_str)
			return (1);
		input = readline(">");
	}
	free(input);
	write (fd, output_str, ft_strlen(output_str));
	free(output_str);
	return (0);
}
