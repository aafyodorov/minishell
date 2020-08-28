/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 13:01:23 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/28 14:46:47 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO check Norm libft!!!

#include "parser.h"

#include <stdio.h>

//TODO Check " ' at string start?
const char		*get_next_part(const char *str, int *key, t_list **list, char *eot)
{
	const char	*ptr;

	*key = is_delim(str, eot);
//	if (*eot && (*key == 0 || *key == 10))
//		*key = -1;
	ptr = NULL;
		if (*key != -1)
		{
			//params = set_params(*key, eot);
			ptr = g_delims[*key].func(str, list, eot);
		}
		else
			ptr = got_literal(str, list,eot);
	return (ptr);
}

//TODO ignore some delimiters -> \ '
//TODO write test when add_node() return 1 (check mem leaks)
//TODO reverse list
/*
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
}*/

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

t_list			*parser(const char *str)
{

	t_list		*list;

	list = NULL;
	if (!rec_parser(str, &list, ""))//temp
		return (NULL);
	ft_lstreverse(&list);
	return (list);
}
