/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 23:35:53 by fgavin            #+#    #+#             */
/*   Updated: 2020/10/01 18:40:49 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

const char	*got_double_delimiter(const char *start, t_list **list,
									const char *params)
{
	t_list		*node;
	unsigned	flag;

	flag = (*params && *(start + 2) && *(start + 2) != *params) ? 1 : 0;
	node = create_node(start, 2, flag, *list);
	if (push_node(list, node))
		return (NULL);
	return (start + 2);
}

const char	*got_dollar(const char *start, t_list **list, const char *params)
{
	char		*ptr;
	t_list		*node;
	unsigned	flag;
	const char	*data;
	size_t		len;

	ptr = *(start + 1) != *params ? get_var(start + 1) : (char*)start + 1;
	flag = (*params && *ptr && *ptr != *params) ? 1 : 0;
	data = (ptr - start == 1) ? "$" : start + 1;
	len = (ptr - start == 1) ? 1 : ptr - start - 1;
	node = create_node(data, len, flag, *list);
	if (ptr - start != 1)
		set_flag_p(node, 2u | get_flag_p(node));
	if (push_node(list, node))
		return (NULL);
	return (ptr);
}

const char	*got_double_quotes(const char *start, t_list **list,
			const char *params)
{
	(void)params;
	if (*(++start) == '\"')
		return (push_node(list, create_node("", 0, 0, *list)) ?
			NULL : start + 1);
	else
		return (rec_parser(start, list, "\""));
}

const char	*got_unit_delimiter(const char *start, t_list **list,
				const char *params)
{
	t_list		*node;
	unsigned	flag;

	flag = (*(++start) && *params && *start != *params) ? 1 : 0;
	flag |= !*params ? 32u : 0;
	node = create_node(start - 1, 1, flag, *list);
	if (push_node(list, node))
		return (NULL);
	return (start);
}
