/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:41:58 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/20 15:27:10 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_abs_d(double a)
{
	return (a * (a >= 0) - a * (a < 0));
}

double	abs_max_d(double a, double b)
{
	a = ft_abs_d(a);
	b = ft_abs_d(b);
	return (ft_max_d(a, b));
}

double	abs_min_d(double a, double b)
{
	a = ft_abs_d(a);
	b = ft_abs_d(b);
	return (ft_min_d(a, b));
}

double	abs_max_signed_d(double a, double b)
{
	double	res;

	res = (abs_max_d(a, b) == ft_abs_d(a));
	return (a * res + b * !res);
}

double	abs_min_signed_d(double a, double b)
{
	double	res;

	res = (abs_min_d(a, b) == ft_abs_d(a));
	return (a * res + b * !res);
}
