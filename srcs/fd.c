/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 21:40:24 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/12 22:07:01 by pdemocri         ###   ########.fr       */
=======
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 02:44:12 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/12 02:44:40 by fgavin           ###   ########.fr       */
>>>>>>> 41af8fc1cc432629be1c3ff6fb5f00e3112c0343
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <fcntl.h>
#include "libft.h"
#include "minishell.h"
#include "redirect.h"

void	save_stdin_stdout(void)
{
<<<<<<< HEAD
	g_fd[0] = dup(0);
	g_fd[1] = dup(1);
=======
	int	i;
	int	fd;

	i = 0;
	while (parse)
	{
		i = is_redirect(get_str(parse));
		if (i == 3 || i == 4 || i == 5)
		{
			if (i == 3 && parse->next)
				fd = open(get_str(parse->next), O_RDONLY |
				O_TRUNC | O_CREAT, 0777);
			if (i == 4 && parse->next)
				fd = open(get_str(parse->next), O_RDONLY |
				O_APPEND | O_CREAT, 0777);
			if (i == 5 && parse->next)
				fd = open(get_str(parse->next), O_WRONLY, 0777);
			if (!*fd_head)
				*fd_head = ft_lstnew_fd(fd);
			else
				ft_lstadd_back_fd(fd_head, ft_lstnew_fd(fd));
		}
		parse = parse->next;
	}
	*fd_list = *fd_head;
>>>>>>> 41af8fc1cc432629be1c3ff6fb5f00e3112c0343
}

int		open_stdin_stdout(void)
{
	dup2(g_fd[1], 1);
	// dup2(g_fd[0], 0); ////////// ???
	return (0);
}
<<<<<<< HEAD
=======

void	read_pipe(t_fd **fd_list)
{
	char	buf;
	t_fd	*tmp;

	while (read(g_pipe[0], &buf, 1) > 0)
		write((*fd_list)->fd, &buf, 1);
	// write((*fd_list)->fd, "\0", 1);
	tmp = *fd_list;
	*fd_list = (*fd_list)->next;
	close(tmp->fd);
	free(tmp);
}
>>>>>>> 41af8fc1cc432629be1c3ff6fb5f00e3112c0343
