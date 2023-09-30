/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 01:52:01 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/31 01:53:10 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap_i(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_d(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
