/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:52:13 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/06 18:12:51 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] && i <= start)
		i++;
	if (start > i)
	{
		if (!(str = (char *)ft_calloc(1, sizeof(char))))
			return (NULL);
		return (str);
	}
	i = 0;
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	while (len > 0 && s[i])
	{
		str[i++] = s[start++];
		len--;
	}
	return (str);
}
