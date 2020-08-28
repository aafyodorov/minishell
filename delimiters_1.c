/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 18:43:51 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/28 14:46:23 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//TODO delete this func
const char	*stub(const char *start, t_list **list, const char *params)
{
	params = NULL;
	list = NULL;
	start = NULL;
	return (NULL);
}

const char	*got_backslash(const char *start, t_list **list, const char *params)
{
	t_list		*node;
	unsigned	flag;

	flag = (*params && *(start + 2) && *(start + 2) != *params) ? 1 : 0;
	node = create_node(start + 1, 1, flag);
	if (push_node(list, node))
		return (NULL);
	return (start + 2);
}

const char	*got_space(const char *start, t_list **list, const char *params)
{
	t_list		*node;
	unsigned	flag;

	while (*start == ' ' && *start != *params)
		start++;
	flag = (*params && *params != *start) ? 1 : 0;
	node = create_node(" ", 1, flag);
	if (push_node(list, node))
		return (NULL);

	return (start);
}

//Todo handle single '
//TODO check sing quotes in double
const char	*got_sing_quote(const char *start, t_list **list, const char *params)
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
	node = create_node(start, next - start - 1, flag);
	if (push_node(list, node))
		return (NULL);
	return (next);
}

const char	*got_literal(const char *start,  t_list **list, const char *params)
{
	const char	*next;
	t_list		*node;
	unsigned	flag;

	next = start;
	while (*next != *params && is_delim(next, params) == -1)
		next++;
	flag = (*next && *next != *params) ? 1 : 0;
	node = create_node(start, next - start, flag);
	if (push_node(list, node))
		return (NULL);
	return (next);
}

const char	*got_unit_delimiter(const char *start,  t_list **list, const char *params)
{
	t_list		*node;
	unsigned	flag;

	flag = (*(++start) && *start != *params) ? 1 : 0;
	node = create_node(start - 1, 1, flag);
	if (push_node(list, node))
		return (NULL);
	return (start);
}