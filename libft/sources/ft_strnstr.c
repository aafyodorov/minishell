/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:51:35 by pdemocri          #+#    #+#             */
/*   Updated: 2020/04/25 12:08:25 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	len2;
	char	*ptr;

	len2 = ft_strlen(str2);
	ptr = (char *)str1;
	if (!len2)
		return (ptr);
	i = 0;
	while (str1[i] && (i + len2) <= n)
	{
		if (*str2 == ptr[i])
		{
			if (!ft_strncmp(&ptr[i], str2, len2))
				return (&ptr[i]);
		}
		i++;
	}
	return (NULL);
}
