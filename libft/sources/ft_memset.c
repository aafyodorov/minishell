/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:48:48 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/09 01:01:08 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char *ptr;

	ptr = (unsigned char *)destination;
	while (n > 0)
		ptr[--n] = c;
	return (destination);
}
