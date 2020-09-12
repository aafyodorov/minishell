/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 02:49:17 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/12 02:49:24 by fgavin           ###   ########.fr       */
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
	if (!ft_strcmp(args[0], "-n"))
	{
		flag = 1;
		i++;
	}
	while (args[i])
		ft_printf("%s", args[i++]);
	if (!flag)
		ft_printf("\n");
	// exit(0);
}
