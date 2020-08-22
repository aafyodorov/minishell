/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:48:41 by pdemocri          #+#    #+#             */
/*   Updated: 2020/04/25 11:48:42 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_t;
	unsigned char	*src_t;

	dst_t = (unsigned char *)dst;
	src_t = (unsigned char *)src;
	if (dst_t < src_t)
	{
		while (n)
		{
			*dst_t++ = *src_t++;
			n--;
		}
	}
	if (dst_t > src_t)
	{
		while (n)
		{
			n--;
			dst_t[n] = src_t[n];
		}
	}
	return (dst);
}
