/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:41:58 by fedmarti          #+#    #+#             */
/*   Updated: 2023/10/10 21:55:34 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int a)
{
	return (a * (a >= 0) - a * (a < 0));
}

int	ft_abs_max(int a, int b)
{
	a = ft_abs(a);
	b = ft_abs(b);
	return (ft_max(a, b));
}

int	ft_abs_min(int a, int b)
{
	a = ft_abs(a);
	b = ft_abs(b);
	return (ft_min(a, b));
}

int	ft_abs_max_signed(int a, int b)
{
	int	res;

	res = (ft_abs_max(a, b) == ft_abs(a));
	return (a * res + b * !res);
}

int	ft_abs_min_signed(int a, int b)
{
	int	res;

	res = (ft_abs_min(a, b) == ft_abs(a));
	return (a * res + b * !res);
}
