/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 03:00:44 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/12 03:00:46 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

void	ctrl_c(int sig)
{
	write(1, "\n\r", 2);
	show_prompt();
}

void	ctrl_b(int sig)
{
	if (g_fork_flag)
		exit(0);
	else
		write(0, "\b\b  \b\b", 6);
}

void	ctrl_d(void)
{
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
