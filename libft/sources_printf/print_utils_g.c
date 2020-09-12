/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_g.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 00:44:22 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/09 01:01:08 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

void	float_gparams(char buf[D_SIZE])
{
	int		i;

	i = ft_strlen(buf) - 1;
	while (i && (buf[i] == '0' || buf[i] == '.'))
	{
		if (buf[i] == '.')
		{
			buf[i] = 0;
			return ;
		}
		buf[i] = 0;
		i--;
	}
}

int		len_gnumber(double d)
{
	int		len;

	d = ft_abs(d);
	len = 0;
	while (d < 1 && d != 0)
	{
		d *= 10;
		len++;
	}
	while (d > 10)
	{
		d /= 10;
		len++;
	}
	return (++len);
}
