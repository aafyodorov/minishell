/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 23:35:53 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/28 14:46:44 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

const char	*got_double_delimiter(const char *start, t_list **list, const char *params)
{
	t_list		*node;
	unsigned	flag;

	flag = (*(start + 2) && *(start + 2) != *params) ? 1 : 0;
	node = create_node(start, 2, flag);
	if (push_node(list, node))
		return (NULL);
	return (start + 2);
}

//TODO Case: single $ must work
const char	*got_dollar(const char *start, t_list **list, const char *params)
{
	char		*ptr;
	t_list		*node;
	unsigned	flag;
	const char	*data;
	size_t		len;

	ptr = get_var(start + 1);
	flag = (*ptr && *ptr != *params) ? 1 : 0;
	data = (ptr - start == 1) ? "$" : start + 1;
	len = (ptr - start == 1) ? 1 : ptr - start -1;
	node = create_node(data, len, flag);
	if (ptr - start != 1)
		set_flag(node, 2u | get_flag(node));
	if (push_node(list, node))
		return (NULL);
	return (ptr);
}


/*const char	*got_dollar(const char *start, t_list **list, const char *params)
{
	char		*ptr;
	t_list		*node;
	unsigned	flag;

	ptr = (char*)start;
	if (*(++ptr) == *params || is_delim(ptr, params) >= 0)
	{
		flag = (*++ptr && *ptr != *params) ? 1 : 0;
		node = create_node("$", 1, flag);
		//ptr++;
	}
	else
	{
		while(is_delim(ptr, params) == -1 && *ptr != *params)
			ptr++;
		flag = (*ptr && *ptr != *params) ? 1 : 0;
		node = create_node(start + 1, ptr - start - 1, flag);
		set_flag(node, 2u | get_flag(node));
	}
	if (push_node(list, node))
		return (NULL);
	return (ptr);
}*/

//TODO Handle incorrect quotes
const char	*got_double_quotes(const char *start, t_list **list, const char *params)
{
	params = NULL;
	return (rec_parser(start + 1, list, "\""));
}