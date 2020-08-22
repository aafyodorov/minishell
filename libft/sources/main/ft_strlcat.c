/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:50:21 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/04 17:46:00 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t i;
	size_t length;

	i = 0;
	while (dst[i] && i < n)
		i++;
	length = ft_strlen(src) + i;
	if (i < n)
	{
		while (i < n - 1 && *src)
			dst[i++] = *src++;
		dst[i] = '\0';
	}
	return (length);
}
