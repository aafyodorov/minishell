/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:33:53 by pdemocri          #+#    #+#             */
/*   Updated: 2020/04/25 12:34:30 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>

void	ft_putendl(char const *s)
{
	int i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		if (write(1, &s[i], 1))
			i++;
	}
	if (!(write(1, "\n", 1)))
		return ;
}
