/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:56 by pdemocri          #+#    #+#             */
/*   Updated: 2020/08/25 01:58:17 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_func(char *str)
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

int	check_operator(char *str)
{
	return (!ft_strcmp(str, ";") || !ft_strcmp(str, "|") ||
			!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") ||
			!ft_strcmp(str, "<"));
}
