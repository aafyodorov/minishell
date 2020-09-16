/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 21:40:24 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/17 00:53:46 by pdemocri         ###   ########.fr       */
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
//proverki