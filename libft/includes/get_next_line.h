/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 23:39:44 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/09 01:01:08 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 100

typedef struct		s_gnl
{
	int				fd;
	char			*tail;
	struct s_gnl	*next;
}					t_list_gnl;

int					get_next_line(int fd, char **line);
t_list_gnl			*ft_lstnew_gnl(t_list_gnl **list, int fd);
int					ft_delnode(t_list_gnl **list, int fd);
int					lstclear_gnl(t_list_gnl **lst, void (*del)(void *));

#endif
