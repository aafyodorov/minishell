/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:31:20 by pdemocri          #+#    #+#             */
/*   Updated: 2020/04/25 12:31:36 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "libft.h"

int	ft_putnbr(long long n)
{
	long long	num;
	int			len;

	len = 0;
	if (n == LLONG_MIN)
		return (write(1, "-9223372036854775808", 20));
	if (n < 0)
	{
		len += ft_putchar('-');
		num = (long long int)(n * -1);
	}
	else
		num = (long long int)n;
	if (num >= 10)
		len += ft_putnbr(num / 10);
	return (len += ft_putchar((char)(num % 10 + '0')));
}
