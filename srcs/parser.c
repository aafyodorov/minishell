/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 13:01:23 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/28 21:46:45 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO check Norm libft!!!

#include "parser.h"

#include <stdio.h>

const char		*get_next_part(const char *str, int *key, t_list **list, char *eot)
{
	const char	*ptr;

	*key = is_delim(str, eot);
	ptr = NULL;
		if (*key != -1)
			ptr = g_delims[*key].func(str, list, eot);
		else
			ptr = got_literal(str, list,eot);
	return (ptr);
}

//TODO write test when add_node() return 1 (check mem leaks)
const char		*rec_parser(const char *str, t_list **list, char *eot)
{
	const char	*ptr;
	int			key;
	while (*str != *eot)
	{
		ptr = NULL;
		key = -1;
		if (!(ptr = get_next_part(str, &key, list, eot)))
		{
			ft_lstclear(list, free);
			return (NULL);
		}
		str = ptr;
	}
	str += (*str == *eot && *eot) ? 1 : 0;
	return (str);
}

void			ft_lstreverse(t_list **list)
{
	t_list		*tmp1;
	t_list		*tmp2;
	t_list		*head;

	head = NULL;
	while (*list)
	{
		tmp1 = *list;
		while (tmp1->next)
			tmp1 = tmp1->next;
		tmp2 = head;
		head = tmp1->next;
		head->next = tmp2;
		tmp1->next=NULL;
	}
	*list = head;
}

t_list			*parser(const char *str)
{

	t_list		*list;

	list = NULL;
	if (!rec_parser(str, &list, ""))//temp
		return (NULL);
	ft_lstreverse(&list);
	return (list);
}
