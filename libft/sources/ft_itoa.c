/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:47:39 by pdemocri          #+#    #+#             */
/*   Updated: 2020/04/25 12:10:34 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_itoa(int n)
{
	unsigned int	len;
	unsigned int	tmp;
	int				sign;
	char			*str;

	if (!n)
		return (ft_strdup("0"));
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
