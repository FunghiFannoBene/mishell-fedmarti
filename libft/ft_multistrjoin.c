/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multistrjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:30:22 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/04 22:59:58 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_multistrjoin(char **strings)
{
	char	*str;
	int		tot_len;
	int		i;

	if (!strings || !*strings)
		return (NULL);
	i = 0;
	tot_len = 1;
	while (strings[i])
	{
		tot_len += ft_strlen(strings[i]);
		i++;
	}
	str = malloc(tot_len * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	tot_len = 0;
	while (strings[i])
	{
		tot_len += (int)ft_strlcpy(str + tot_len, strings[i], INT_MAX);
		i++;
	}
	str[tot_len] = 0;
	return (str);
}
