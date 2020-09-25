/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:05:34 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/18 21:38:25 by pdemocri         ###   ########.fr       */
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
		while (!ft_strcmp(args[i], "-n"))
		{
			flag = 1;
			i++;
		}
		while (args[i])
			ft_printf("%s", args[i++]);
	}
	if (!flag)
		ft_printf("\n");
	return (0);
}
