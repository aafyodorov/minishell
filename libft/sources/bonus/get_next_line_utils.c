/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 23:40:10 by pdemocri          #+#    #+#             */
/*   Updated: 2020/05/16 01:10:54 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

t_list_gnl	*ft_lstnew_gnl(t_list_gnl **list, int fd)
{
	t_list_gnl	*new;

	if (!(new = (t_list_gnl *)malloc(sizeof(t_list_gnl))))
		return (NULL);
	new->tail = NULL;
	new->next = NULL;
	new->fd = fd;
	if (!(*list))
		*list = new;
	else
	{
		new->next = *list;
		*list = new;
	}
	return (*list);
}

int			ft_delnode(t_list_gnl **list, int fd)
{
	t_list_gnl *prev;
	t_list_gnl *curr;

	prev = *list;
	curr = *list;
	while (curr->fd != fd)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev->next != curr->next)
		prev->next = curr->next;
	else
		*list = (*list)->next;
	free(curr);
	return (0);
}
