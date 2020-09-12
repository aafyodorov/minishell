/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 02:44:12 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/12 02:44:40 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <fcntl.h>
#include "minishell.h"
#include "redirect.h"

t_fd	*ft_lstnew_fd(int fd)
{
	t_fd *list;

	list = (t_fd *)ft_calloc(sizeof(t_fd), 1);
	if (list)
		list->fd = fd;
	return (list);
}

void	ft_lstadd_back_fd(t_fd **lst, t_fd *new)
{
	t_fd *tmp;

	if (lst && *lst)
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (lst)
		*lst = new;
}

void	open_fd(t_list *parse, t_fd **fd_head, t_fd **fd_list)
{
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
}

void	close_fd(t_fd **fd_head)
{
	t_fd	*tmp;

	while (*fd_head)
	{
		tmp = (*fd_head)->next;
		close((*fd_head)->fd);
		free(*fd_head);
		*fd_head = tmp;
	}
}

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
