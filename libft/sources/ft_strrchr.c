/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:51:42 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/15 21:05:12 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int		i;
	char	*ptr;

	i = ft_strlen(str);
	ptr = (char *)str;
	while (i >= 0)
	{
		if (ptr[i] == (char)ch)
			return (&ptr[i]);
		i--;
	}
	return (NULL);
}
