/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 18:36:47 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/23 19:48:30 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list		*create_node(const char *data, size_t len)
{
	t_list		*node;
	char		*n_data;

	if (!((n_data = malloc(++len * sizeof(char))) &&
		(node = ft_lstnew(NULL))))
	{
		free(n_data);
		free(node);
		return (NULL);
	}
	ft_strlcpy(n_data, data, len);
	node->content = n_data;
	printf("! %s\n", n_data);
	return (node);
}

int		push_node(t_list **list, t_list *new_node)
{
	if (!new_node)
		return (1);
	if (!*list)
		*list = new_node;
	else
		ft_lstadd_front(list, new_node);
	return (0);
}

int			is_delim(const char *str)
{
	int			i;
	const char	*ptr;

	i = -1;
	while (++i < DELIM_NUM)
	{
		ptr = str;
		if (!ft_strncmp(ptr, g_delims[i].data, i == DELIM_NUM - 1 ? 2 : 1))
			return (i);
	}
	return (-1);
}