/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:56 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/08 17:39:51 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_func(char *str)
{
	const char	*funcs_str[8] = {NULL,
								"echo",
								"cd",
								"pwd",
								"export",
								"unset",
								"env",
								"exit"};
	int			i;

	i = 0;
	while (++i < 8)
		if (!ft_strcmp(funcs_str[i], str))
			return (i);
	return (0);
}

int	is_redirect(char *str)
{
	int			i;
	const char	redir[6][3] = {"", ";", "|", ">", ">>", "<"};

	i = 0;
	while (++i < 6)
	{
		if (!ft_strcmp(str, redir[i]))
			return (i);
	}
	return (0);
}
