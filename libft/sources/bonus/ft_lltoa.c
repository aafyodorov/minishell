/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:46:32 by pdemocri          #+#    #+#             */
/*   Updated: 2020/06/05 01:49:18 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <limits.h>
#include "libft.h"

char		*ft_lltoa(long long n)
{
	unsigned int		len;
	unsigned long long	tmp;
	int					sign;
	char				*str;

	if (!n)
		return (ft_strdup("0"));
	if (n == LLONG_MIN)
		return (ft_strdup("−9223372036854775808"));
	sign = n > 0 ? 1 : -1;
	tmp = n * sign;
	len = n < 0 ? 2 : 1;
	while ((n /= 10))
		len++;
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	if (sign < 0)
		str[0] = '-';
	len--;
	while (tmp)
	{
		str[len--] = tmp % 10 + '0';
		tmp /= 10;
	}
	return (str);
}
