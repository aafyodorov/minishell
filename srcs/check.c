/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:56 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/03 13:22:30 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_func(char *str)
{
	const char	*funcs_str[7] = {"echo",
								"cd",
								"pwd",
								"export",
								"unset",
								"env",
								"exit"};
	int			i;

	i = 0;
	while (i < 7)
		if (!ft_strcmp(funcs_str[i++], str))
			return (i - 1);
	return (-1);
}

int	is_redirect(char *str)
{
	int			i;
	const char	*redirects[6] = {" ", ";", "|", ">", ">>", "<"};


	i = 0;
	while (++i < 6)
	{
		if (!ft_strcmp(redirects[i], str))
			return (i);
	}
	return (0);
}
