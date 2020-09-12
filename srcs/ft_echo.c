/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:05:34 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/12 22:09:34 by pdemocri         ###   ########.fr       */
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
			ft_printf("%s", args[i++]);
	}
	if (!flag)
		ft_printf("\n");
<<<<<<< HEAD
	return (0);
}

/////////////////// сег фолт при попытке распечать несуществующую переменную
=======
	// exit(0);
}
>>>>>>> 41af8fc1cc432629be1c3ff6fb5f00e3112c0343
