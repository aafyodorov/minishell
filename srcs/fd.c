/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 21:40:24 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/19 03:31:23 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <fcntl.h>
#include "libft.h"
#include "minishell.h"
#include "redirect.h"

void	save_stdin_stdout(void)
{
	g_fd[0] = dup(0);
	g_fd[1] = dup(1);
}

int		open_stdin_stdout(void)
{
	dup2(g_fd[1], 1);
	if (g_pipe_prev != 2)
		dup2(g_fd[0], 0);
	return (0);
}

int		open_pipe_parent(void)
{
	if (g_pipe_next == 2)
	{
		dup2(g_pipe[0], 0);
		close(g_pipe[1]);
	}
	return (0);
}

int		open_pipe_child(void)
{
	if (g_pipe_next == 2)
	{
		dup2(g_pipe[1], 1);
		close(g_pipe[0]);
	}
	return (0);
}
