/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:05:40 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/16 22:42:29 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "minishell.h"

int	ft_exit(char **args, unsigned flag)
{
	(void)flag;
	if ((args = NULL))
		return (0);
	super_ctrl_d();
	return (0);
}
