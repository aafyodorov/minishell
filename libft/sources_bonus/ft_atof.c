/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 06:07:45 by pdemocri          #+#    #+#             */
/*   Updated: 2020/06/15 06:08:03 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	get_float(char *str)
{
	int		i;
	float	flt;

	flt = 0;
	i = ft_strlen(str);
	while (i--)
		flt = (flt + (str[i] - '0')) / 10;
	return (flt);
}

double			ft_atof(char *str)
{
	double	f;
	double	nb;
	double	sign;

	nb = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -sign;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	if (*str == '.')
	{
		f = get_float(++str);
		nb += f;
	}
	nb *= sign;
	return ((float)nb);
}
