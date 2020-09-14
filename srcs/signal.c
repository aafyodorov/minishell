/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 03:00:44 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/15 00:52:31 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

void	ctrl_c(int sig)
{
	write(1, "\n\r", 2);
	g_exit_status = 130;
	show_prompt();
}

void	ctrl_b(int sig)
{
	if (!g_fork_flag)
		write(0, "\b\b  \b\b", 6);
}

void	ctrl_d(void)
{
	ft_printf("%i\n", g_pipe_next);
	free_args(&g_env_vars);
	ft_lstclear(&g_loc_vars, del_var_cont);
	printf("In ctrl_D\n");
	exit(0);
}

void	signal_handler(void)
{
	if (signal(SIGINT, ctrl_c) == SIG_ERR)
		g_exit_status = errno;
	signal(SIGQUIT, ctrl_b);
}
