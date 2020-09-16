/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 18:43:51 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/17 01:02:28 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

const char	*got_backslash(const char *start, t_list **list, const char *params)
{
	t_list		*node;
	unsigned	flag;
	const char	*ptr;
	size_t		len;

	ptr = start;
	while (*ptr == '\\')
		ptr++;
	len = ptr - start;
	flag = (*params && *ptr && *ptr != *params) ? 1 : 0;
	if (len % 2 && *ptr == *params)
		return (NULL);
	else if (len % 2 == 0)
		len /= 2;
	else if (len == 1)
		;
	else
		len = len / 2 + 1;
	node = create_node(start + len, len, flag, *list);
	if (push_node(list, node))
		return (NULL);
	ptr += ((ptr - start) % 2) ? 1 : 0;
	return (ptr);
}

const char	*got_space(const char *start, t_list **list, const char *params)
{
	t_list		*node;
	unsigned	flag;

	while ((*start == ' ' || *start == '\t') && *start != *params)
		start++;
	flag = (*params && *params != *start) ? 1 : 0;
	node = create_node(" ", 1, flag, *list);
	if (push_node(list, node))
		return (NULL);
	return (start);
}

const char	*got_sing_quote(const char *start, t_list **list,
				const char *params)
{
	t_list		*node;
	const char	*next;
	unsigned	flag;

	start++;
	next = start;
	while (*next != '\'')
	{
		if (*next == *params)
			return (NULL);
		++next;
	}
	flag = (*(++next) && *params && *next != *params) ? 1 : 0;
	node = create_node(start, next - start - 1, flag, *list);
	if (push_node(list, node))
		return (NULL);
	return (next);
}

const char	*got_literal(const char *start, t_list **list, const char *params)
{
	char		*next;
	t_list		*node;
	unsigned	flag;

	flag = 0;
	next = (char *)start;
	while (*next != *params && is_delim(next, params) == -1)
	{
		if (*next == '=')
			return (got_var((char *)start, next, (char *)params, *list));
		next++;
	}
	node = create_node(start, next - start, 0, *list);
	flag |= (*params && *next && *next != *params) ? 1u : 0;
	if (push_node(list, node))
		return (NULL);
	flag |= *list && !ft_strcmp(get_str(*list), "export") ? 4u : 0;
	set_flag_parser(*list, get_flag_parser(*list) | flag);
	next += *next == '\003' ? 1 : 0;
	return (next);
}

const char	*got_unit_delimiter(const char *start, t_list **list,
				const char *params)
{
	t_list		*node;
	unsigned	flag;

	flag = (*(++start) && *params && *start != *params) ? 1 : 0;
	node = create_node(start - 1, 1, flag, *list);
	if (push_node(list, node))
		return (NULL);
	return (start);
}
