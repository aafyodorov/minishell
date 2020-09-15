/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 21:40:24 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/15 05:25:36 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <fcntl.h>
#include "libft.h"
#include "minishell.h"
#include "redirect.h"

int		save_stdin_stdout(void)
{
	if ((g_fd[0] = dup(0) == -1 ||
		(g_fd[1] = dup(1) == -1)))
		return (print_error(strerror(errno), 1));
	return (0);
}

int		open_stdin_stdout(void)
{
	if (dup2(g_fd[1], 1) == -1)
		return (print_error(strerror(errno), 1));
	if (g_pipe_prev != 2)
	{
		if (dup2(g_fd[0], 0) == -1)
			return (print_error(strerror(errno), 1));
	}
	return (0);
}
