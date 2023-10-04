/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strhas.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:17:25 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/04 22:21:02 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strhas(char *str, char *charset)
{
	int	i;

	if (!str || !charset)
		return (0);
	while (*str)
	{
		i = 0;
		while (charset[i])
		{
			if (*str == charset[i])
				return (1);
			i++;
		}
		str++;
	}
	return (0);
}
