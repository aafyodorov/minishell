/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 03:00:44 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/16 22:28:55 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

void	ctrl_c(int sig)
{
	sig = 0;
	//ft_printf("~~~~~~");
	write(1, "\n\r", 2);
	show_prompt();
	g_exit_status = 130;
	if (g_fork_flag)
	{

		exit (errno);
	}
	g_prompt = 1;
}

void	ctrl_b(int sig)
{
	sig = 0;
	if (!g_fork_flag)
		write(0, "\b\b  \b\b", 6);
}

void	ctrl_d(void)
{
	free_args(&g_env_vars);
	ft_lstclear(&g_loc_vars, del_var_cont);
	exit(0);
}

void	super_ctrl_d(void)
{
	ft_putchar(10);
	ctrl_d();
}

void	signal_handler(void)
{
	if (signal(SIGINT, ctrl_c) == SIG_ERR)
		g_exit_status = errno;
	signal(SIGQUIT, ctrl_b);
}
