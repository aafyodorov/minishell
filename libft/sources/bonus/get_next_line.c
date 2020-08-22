/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 23:40:33 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/16 01:10:03 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"

static int	freemem(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (0);
}

static int	check_tail(char **tail, char **line)
{
	char			*tmp;
	char			*tmp_line;

	tmp_line = *line;
	if ((tmp = ft_strchr(*tail, '\n')))
	{
		tmp[0] = '\0';
		if (!(*line = ft_strjoin(*line, *tail)))
			return (freemem(&tmp_line) + freemem(tail) - 1);
		*tail = ft_strcpy(*tail, ++tmp);
		return (freemem(&tmp_line) + 1);
	}
	else
	{
		if (!(*line = ft_strjoin(*line, *tail)))
			return (freemem(&tmp_line) + freemem(tail) - 1);
		return (freemem(&tmp_line) + freemem(tail) + 2);
	}
}

static int	check_buf(char *buf, char **tail, char **line)
{
	char			*tmp;
	char			*tmp_line;

	tmp_line = *line;
	if ((tmp = ft_strchr(buf, '\n')))
	{
		tmp[0] = '\0';
		if (!(*line = ft_strjoin(*line, buf)))
			return (freemem(&tmp_line) + freemem(&buf) - 1);
		if (!(*tail = ft_strjoin(++tmp, "")))
			return (freemem(&tmp_line) + freemem(&buf) - 1);
		return (freemem(&tmp_line) + freemem(&buf) + 1);
	}
	else
	{
		if (!(*line = ft_strjoin(*line, buf)))
			return (freemem(&tmp_line) + freemem(&buf) - 1);
		return (freemem(&tmp_line) + 2);
	}
}

int			get_line(int fd, char **line, char **tail, t_list_gnl **list)
{
	int				res;
	int				readed;
	char			*buf;

	res = 0;
	if (*tail && (res = check_tail(tail, line)) != 2)
		return ((res == -1) ? ft_delnode(list, fd) : res);
	if (!(buf = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (freemem(tail) + ft_delnode(list, fd) - 1);
	while ((readed = read(fd, buf, BUFFER_SIZE)))
	{
		if (readed < 0)
			return (freemem(&buf) + ft_delnode(list, fd) - 1);
		buf[readed] = '\0';
		if ((res = check_buf(buf, tail, line)) != 2)
			return (res != 1 ? ft_delnode(list, fd) : res);
	}
	return (res == 0 ? ft_delnode(list, fd) + freemem(&buf) + freemem(line) :\
	ft_delnode(list, fd) + freemem(&buf) + 1);
}

int			get_next_line(int fd, char **line)
{
	static t_list_gnl	*list;
	t_list_gnl			*tmp;

	if (!line || fd < 0 || BUFFER_SIZE < 1 ||
	!(*line = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	*line[0] = 0;
	if (!list)
		if (!(list = ft_lstnew_gnl(&list, fd)))
			return (-1);
	tmp = list;
	while (tmp->next && fd != tmp->fd)
		tmp = tmp->next;
	if (fd != tmp->fd)
	{
		if (!(list = ft_lstnew_gnl(&list, fd)))
			return (-1);
		tmp = list;
	}
	return (get_line(fd, line, &(tmp->tail), &list));
}
