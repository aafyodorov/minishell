/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:05:52 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/18 04:27:17 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libftprintf.h"

int	ft_pwd(char **args)
{
	char		homepath[1024];

	(void)args;
	if (!getcwd(homepath, 1024))
		return (print_error(strerror(errno), 1));
	ft_printf("%s\n", homepath);
	return (0);
}
