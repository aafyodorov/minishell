/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 02:51:35 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/12 02:51:35 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

int	ft_pwd(char **args)
{
	char		homepath[1024];

	getcwd(homepath, 1024);
	ft_printf("%s\n", homepath);
	// exit(0);
}
