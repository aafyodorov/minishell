/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:46:23 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/18 05:20:30 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*buf;

	if ((n && SIZE_MAX / n < size) || (size && SIZE_MAX / size < n))
		return (NULL);
	if (!(buf = (void *)malloc(size * n)))
		return (NULL);
	ft_bzero(buf, size * n);
	return (buf);
}
