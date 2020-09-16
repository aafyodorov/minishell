/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:48:03 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/15 21:05:12 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *arr, int ch, size_t n)
{
	size_t	i;
	char	*buf;

	i = 0;
	buf = (char *)arr;
	while (i < n)
	{
		if (buf[i] == (char)ch)
			return (&buf[i]);
		i++;
	}
	return (NULL);
}
