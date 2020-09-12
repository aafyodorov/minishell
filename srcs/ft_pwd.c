/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:05:52 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/12 22:05:54 by pdemocri         ###   ########.fr       */
=======
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 02:51:35 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/12 02:51:35 by fgavin           ###   ########.fr       */
>>>>>>> 41af8fc1cc432629be1c3ff6fb5f00e3112c0343
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libftprintf.h"

int	ft_pwd(char **args)
{
	char		homepath[1024];

	if (!getcwd(homepath, 1024))
		return (print_error(strerror(errno),1));
	ft_printf("%s\n", homepath);
<<<<<<< HEAD
	return (0);
}
=======
	// exit(0);
}
>>>>>>> 41af8fc1cc432629be1c3ff6fb5f00e3112c0343
