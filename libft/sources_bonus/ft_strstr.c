/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:23:30 by pdemocri          #+#    #+#             */
/*   Updated: 2020/04/25 12:24:22 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strstr(const char *str1, const char *str2)
{
	int		i;
	int		len;
	char	*ptr;

	ptr = (char *)str1;
	len = ft_strlen(str2);
	if (!len)
		return (ptr);
	i = 0;
	while (str1[i])
	{
		if (*str2 == ptr[i])
		{
			if (!ft_strncmp(&ptr[i], str2, len))
			{
				ptr = &ptr[i];
				return (ptr);
			}
		}
		i++;
	}
	return (NULL);
}
