/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:46:23 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/16 06:51:42 by pdemocri         ###   ########.fr       */
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
