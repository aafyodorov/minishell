/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:34:00 by pdemocri          #+#    #+#             */
/*   Updated: 2020/04/25 12:34:13 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include "libft.h"

int	ft_putstr(char const *s)
{
	int i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
	{
		if (write(1, &s[i], 1))
			i++;
	}
	return (i);
}
