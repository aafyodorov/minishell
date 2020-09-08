/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_buf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 00:12:14 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/09 01:01:08 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arr_buf.h"

#include <stdio.h>
void		init_buf(t_buf *buf)
{
	ft_bzero(buf->buf, BUF_SIZE);
	buf->i = 0;
}

int			flush_buf(t_buf *buf, char **str)
{
	char		*tmp;

	if (!*str && !(*str = ft_calloc(1, sizeof(char))))
		return (1);
	if (!(tmp = ft_strjoin(*str, buf->buf)))
	{
		free(*str);
		*str = NULL;
		return (1);
	}
	buf->i = 0;
	buf->buf[0] = 0;//sdfsdf
	free(*str);
	*str = tmp;
	return (0);
}

int			add_to_buf(t_buf *buf, char chr, char **str)
{
	if (buf->i == BUF_SIZE - 1)
	{
		if (flush_buf(buf, str))
		{
			free(*str);
			*str = NULL;
			return (1);
		}
	}
	buf->buf[buf->i] = chr;
	(buf->i)++;
	buf->buf[buf->i] = 0;
	return (0);
}
