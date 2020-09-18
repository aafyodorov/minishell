/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:14 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/18 05:20:30 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "minishell.h"
#include "libft.h"
#include "redirect.h"

int		main(int argc, char **argv, char **envp)
{
	if (argc > 1 || argv[1])
		return (ft_putendl_fd("Error. Invalid arguments\n", 2));
	if (get_envs(envp, &g_env_vars))
		print_error(strerror(errno), 1);
	save_stdin_stdout();
	signal_handler();
	if (!loop_read())
		ft_putendl_fd("Error\n", 2);
	ctrl_d();
}
