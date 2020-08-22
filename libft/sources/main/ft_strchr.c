/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:49:56 by pdemocri          #+#    #+#             */
/*   Updated: 2020/04/25 12:03:49 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	char	*ptr;
	int		i;

	ptr = (char *)str;
	i = ft_strlen(ptr);
	while (i-- >= 0)
	{
		if (*ptr == (char)ch)
			return (ptr);
		ptr++;
	}
	return (NULL);
}
