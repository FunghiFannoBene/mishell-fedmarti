/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:41:58 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/02 23:46:04 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int a)
{
	return (a * (a >= 0) - a * (a < 0));
}

int	abs_max(int a, int b)
{
	a = ft_abs(a);
	b = ft_abs(b);
	return (ft_max(a, b));
}

int	abs_min(int a, int b)
{
	a = ft_abs(a);
	b = ft_abs(b);
	return (ft_min(a, b));
}

int	abs_max_signed(int a, int b)
{
	int	res;

	res = (abs_max(a, b) == ft_abs(a));
	return (a * res + b * !res);
}

int	abs_min_signed(int a, int b)
{
	int	res;

	res = (abs_min(a, b) == ft_abs(a));
	return (a * res + b * !res);
}
