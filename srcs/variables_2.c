/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 03:05:53 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/26 20:21:48 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

int			subst_var(t_list **parse, char **args, int *i)
{
	char		*var_name;

	if (get_flag_p(*parse) & 16u)
	{
		var_name = get_str(*parse);
		if (!(ft_isalpha(var_name[0]) || var_name[0] == '_'))
			return (0);
		got_var(get_str(*parse), ft_strchr(get_str(*parse), '='), parse);
		*args = ft_strdup("\t");
		(*i)++;
		*parse = *parse ? (*parse)->next : NULL;
		return (1);
	}
	return (0);
}

char		*concat_var(char **str, t_list *node, unsigned flag)
{
	*str = flag & 2u ?
		ft_strjoin_free(*str, ft_strdup_arg(get_str(node), flag, g_env_vars),
						3) :
			ft_strjoin_free(*str, get_str(node), 1);
	return (*str);
}

int			add_var_to_env(char **cont)
{
	int			i;
	int			idx;
	char		*tmp;

	i = -1;
	if ((idx = find_env_var(g_env_vars, cont[0])) != -1)
		free(g_env_vars[idx]);
	else
	{
		while (++i < ENV_LENGTH && g_env_vars[i])
			;
		if (i == ENV_LENGTH)
			return (1);
		idx = i;
	}
	tmp = ft_strjoin("=", cont[1]);
	if (!(g_env_vars[idx] = ft_strjoin(cont[0], tmp)))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
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
