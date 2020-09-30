/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:05:40 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/19 00:52:16 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "minishell.h"

static int	isnumber(char *str)
{
	int	i;
	int	res;

	if (!str || !str[0])
		return (0);
	i = -1;
	res = 1;
	if (*str == '-')
		str++;
	while (str[++i] && res)
	{
		if (!ft_isdigit(str[i]))
			res = 0;
	}
	return (res);
}

int			ft_exit(char **args)
{
	(void)args;
	if (args[0])
	{
		if (isnumber(args[0]) && !args[1])
			g_exit_status = (unsigned char)ft_atoi(args[0]);
		else if (isnumber(args[0]))
			return (g_exit_status =
			print_error("exit\nminishell: exit: too many arguments", 1));
		else
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(args[0], 2);
			exit(print_error(": need numeric argument", 2));
		}
	}
	exit(g_exit_status);
}
