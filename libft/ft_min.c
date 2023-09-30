/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:46:12 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/06 20:09:13 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_min(int a, int b)
{
	return (a * (a <= b) + b * (b < a));
}

double	ft_min_d(double a, double b)
{
	return (a * (a <= b) + b * (b < a));
}