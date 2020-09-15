/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 17:57:46 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/15 23:31:15 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stdio.h>
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

int			add_var_to_list(t_list **list, char **cont, int create)
{
	t_list		*tmp_node;
	char		**tmp_cont;

	if ((tmp_node = find_elem(*list, cont[0])))
	{
		free(((char **)(tmp_node->content))[1]);
		if (!(((char **)(tmp_node->content))[1] = ft_strdup(cont[1])))
			return (1);
	}
	else if (create)
	{
		if (!(tmp_cont = ft_calloc(2, sizeof(void*))))
			return (1);
		if (!(tmp_cont[0] = ft_strdup(cont[0])) ||
			!(tmp_cont[1] = ft_strdup(cont[1])))
		{
			del_var_cont(tmp_cont);
			return (1);
		}
		if (!*list)
			*list = ft_lstnew(tmp_cont);
		else
			ft_lstadd_front(list, ft_lstnew(tmp_cont));
	}
	return (0);
}

int			check_var_in_env(char **var_list, char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (var_list[i])
	{
		if (!ft_strncmp(var_list[i], str[0], ft_strlen(str[0])) &&
			var_list[i][ft_strlen(str[0])] == '=')
		{
			tmp = ft_strjoin(str[0], " ");
			var_list[i] = ft_strjoin(tmp, str[1]);
			return (0);
		}
		i++;
	}
	return (0);
}

int			add_var_to_env(char **cont)
{
	int			i;

	i = -1;
	while (++i < ENV_LENGTH && g_env_vars[i])
		;
	if (i == ENV_LENGTH)
		return (1);
	if (!(g_env_vars[i] = ft_strjoin(cont[0],
	ft_strjoin("=", cont[1]))))
		return (1);
	return (0);
}

char		*got_var(const char *start, const char *eq_sign, const char *params,
	t_list *head)
{
	const char	*end;
	char		*cont[2];
	int			err_flg;
	t_list		*tmp;

	err_flg = 0;
	end = eq_sign;
	while (*end && is_delim(end, params) < 0)
		end++;
	if (cr_var_cont(start, eq_sign, end, (char **)cont))
		return (NULL);
	if ((get_flag_parser(head) & 4u) != 0) {
		err_flg = add_var_to_env(cont) ? 1 : 0;
		tmp = head;
		while (tmp && ft_strcmp(get_str(tmp), "export"))
			tmp = tmp->next;
		if (tmp) {
			set_flag_parser(tmp, get_flag_parser(tmp) | 8u);
		//ft_printf("in got_var flag: '%d'\t data: '%s'\n", get_flag_parser(tmp), get_str(tmp));
		}
	}
	else
		check_var_in_env(g_env_vars, cont);
	if (!err_flg && add_var_to_list(&g_loc_vars, cont, 1))
		err_flg = 1;
	free(cont[0]);
	free(cont[1]);
	return (err_flg ? NULL : (char *)end);
}