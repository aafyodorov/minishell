/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 13:01:23 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/23 20:50:23 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stdio.h>

//TODO Check " ' at string start?
const char		*get_next_part(const char *str, int *key, t_list **list)
{
	const char	*ptr;

	ptr = NULL;
		if ((*key = is_delim(str)) != -1)
		{
			ptr = g_delims[*key].func(str, list);
			return ((char *)ptr);
		}
		else
			ptr = got_literal(str, list);
	return (ptr);
}

//TODO write test when add_node() return 1 (check mem leaks)
//TODO reverse list
t_list			*parser(const char *str)
{
	const char	*ptr;
	int			key;
	t_list		*list;

	list = NULL;
	while (*str)
	{
		ptr = NULL;
		key = -1;
		if (!(ptr = get_next_part(str, &key, &list)))
		{
			ft_lstclear(&list, free);
			return (NULL);
		}
		str = ptr;
	}
	//reverse list!
	return (list);
}