/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 17:57:46 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/30 00:38:31 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stdio.h>
void		del_var_cont(void *content)
{
	char	**cont;

	cont = content;
	free(cont[0]);
	cont[0] = NULL;
	free(cont[1]);
	cont[1] = NULL;
	free(cont);
}

int			cr_var_cont(const char *start, const char *eq_sign,
	const char *end, char **content)
{
	size_t		len_name;
	size_t		len_var;

	len_name = eq_sign - start + 1;
	len_var = end - eq_sign + 1;
	content[0] = ft_calloc(len_name, sizeof(char));
	content[1] = ft_calloc(len_var, sizeof(char));
	if (!content[0] || !content[1])
	{
		free(content[0]);
		free(content[1]);
		return (1);
	}
	ft_strncpy(content[0], start, len_name - 1);
	ft_strncpy(content[1], eq_sign + 1, len_var - 1);
	return (0);
}

t_list		*find_elem(t_list *list, char *key)
{
	while (list)
	{
		if (!ft_strcmp(key, ((char **)list->content)[0]))
			return (list);
		list = list->next;
	}
	return (NULL);
}


int			add_var_to_list(t_list **list, char **cont, int create, int *del)
{
	t_list		*tmp_node;
	char		**tmp_cont;

	if ((tmp_node = find_elem(*list, cont[0])))
	{
		free(((char **)(tmp_node->content))[1]);
		((char **)(tmp_node->content))[1] = cont[1];
		*del = 1;
	}
	else if (create)
	{
		if (!(tmp_cont = ft_calloc(2, sizeof(void*))))
			return (1);
		*del = 0;
		tmp_cont[0] = cont[0];
		tmp_cont[1] = cont[1];
		if (!*list)
			*list = ft_lstnew(tmp_cont);
		else
			ft_lstadd_front(list, ft_lstnew(tmp_cont));
	}
	return (1);
}

char		*got_var(char *start, char *eq_sign, char *params, t_list **env)
{
	char		*end;
	char		*cont[2];
	int			del;

	end = eq_sign;
	while (*end && is_delim(end, params) < 0)
		end++;
	if (cr_var_cont(start, eq_sign, end, (char **)cont))
		return (NULL);
	add_var_to_list(env, cont, 0, &del);
	add_var_to_list(&g_loc_vars, cont, 1, &del);
	if (del)
	{
		free(cont[0]);
		//cont[0] = NULL;
	}
	return (end);
}