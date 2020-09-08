/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:25:11 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/09 01:01:08 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if (size == FT_SIZE_MAX)
		return (NULL);
	str = (char *)ft_calloc(size + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	return (str);
}
