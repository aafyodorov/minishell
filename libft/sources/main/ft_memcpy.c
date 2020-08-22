/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:48:33 by pdemocri          #+#    #+#             */
/*   Updated: 2020/04/25 11:48:34 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst_t;
	const unsigned char	*src_t;

	i = 0;
	dst_t = (unsigned char *)dst;
	src_t = (const unsigned char *)src;
	while (i < n && dst != src)
	{
		dst_t[i] = src_t[i];
		i++;
	}
	return (dst);
}
