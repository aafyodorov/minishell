/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:07:21 by pdemocri          #+#    #+#             */
/*   Updated: 2020/06/03 01:07:25 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_pow(double basis, double exponent)
{
	double	res;

	if (exponent == 0)
		return (1);
	res = basis;
	while (--exponent > 0)
		res *= basis;
	return (res);
}
