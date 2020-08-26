/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 23:35:53 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/24 23:36:02 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

const char	*got_double_delimiter(const char *start,  t_list **list)
{
	t_list		*node;

	node = create_node(start, 2);
	if (push_node(list, node))
		return (NULL);
	return (start + 2);
}