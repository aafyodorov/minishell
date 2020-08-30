/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 13:01:23 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/30 15:20:50 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO check Norm libft!!!

#include "parser.h"
#include "libft.h"
#include "minishell.h"

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

t_list			*parser(const char *str)
{

	t_list		*list;

	list = NULL;
	if (!rec_parser(str, &list, ""))//temp
		return (NULL);
	ft_lstreverse(&list);
	ft_delspaces(&list);
	return (list);
}
