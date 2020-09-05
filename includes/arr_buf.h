/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_buf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 00:13:06 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/04 23:13:49 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARR_BUF_H
# define ARR_BUF_H

# include "libft.h"

# define BUF_SIZE 256

typedef struct {
	int		i;
	char	buf[BUF_SIZE + 1];
}			t_buf;

void		init_buf(t_buf *buf);
int			add_to_buf(t_buf *buf, char chr, char **str);
int			flush_buf(t_buf *buf, char **str);

#endif
