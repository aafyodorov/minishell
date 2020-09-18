/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:05:34 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/18 04:27:17 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"
#include "minishell.h"

int			ft_echo(char **args)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (*args)
	{
		if (!ft_strcmp(args[0], "-n"))
		{
			flag = 1;
			i++;
		}
		while (args[i])
		{
			ft_printf("%s", args[i++]);
			if (args[i])
				ft_putchar(' ');
		}
	}
	if (!flag)
		ft_printf("\n");
	return (0);
}
