/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 18:43:51 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/24 23:35:47 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//TODO delete this func
const char	*stub(const char *start, t_list **list)
{
	list = NULL;
	start = NULL;
	return (NULL);
}

const char	*got_backslash(const char *start, t_list **list)
{
	t_list		*node;

	node = create_node(start + 1, 1);
	if (push_node(list, node))
		return (NULL);
	return (start + 2);
}

const char	*got_space(const char *start, t_list **list)
{
	t_list		*node;

	node = create_node(" ", 1);
	while (*start == ' ')
		start++;
	if (push_node(list, node))
		return (NULL);

	return (start);
}

const char	*got_sing_bracket(const char *start, t_list **list)
{
	t_list		*node;
	const char	*next;

	start++;
	next = start;
	while (*next != '\'')
		++next;
	node = create_node(start, next - start);
	if (push_node(list, node))
		return (NULL);
	return (++next);
}

const char	*got_literal(const char *start,  t_list **list)
{
	const char	*next;
	t_list		*node;

	next = start;
	while (is_delim(next) == -1)
		next++;
	node = create_node(start, next - start);
	if (push_node(list, node))
		return (NULL);
	return (next);
}

const char	*got_unit_delimiter(const char *start,  t_list **list)
{
	t_list		*node;

	node = create_node(start, 1);
	if (push_node(list, node))
		return (NULL);
	return (start + 1);
}