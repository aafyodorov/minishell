/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 17:57:46 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/26 16:34:28 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				add_var_to_list(t_list **list, char **cont, int create)
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

int				check_var_in_env(char **var_list, char **str)
{
	int			i;
	char		*tmp;

	i = 0;
	while (var_list[i])
	{
		if (!ft_strncmp(var_list[i], str[0], ft_strlen(str[0])) &&
			var_list[i][ft_strlen(str[0])] == '=')
		{
			tmp = ft_strjoin(str[0], "=");
			var_list[i] = ft_strjoin(tmp, str[1]);
			free(tmp);
			return (0);
		}
		i++;
	}
	return (0);
}

static int		got_var_sub(char **cont, t_list **cur)
{
	int			err_flg;
	unsigned	flag;

	flag = 0;
	cont[1] = ft_calloc(1, sizeof(char));
	err_flg = (cont[1]) ? 0 : 1;
	*cur = (*cur)->next;
	while (!err_flg && *cur && (flag = get_flag_parser(*cur)) & 1u)
	{
		cont[1] = concat_var(&cont[1], *cur, flag);
		err_flg = (cont[1]) ? 0 : 1;
		*cur = (*cur)->next;
	}
	if (*cur)
	{
		cont[1] = concat_var(&cont[1], *cur, flag);
		err_flg = (cont[1]) ? 0 : 1;
	}
	return (err_flg);
}

int				export_check(t_list *head, char **cont)
{
	int			err_flg;

	err_flg = 0;
	if (head && (get_flag_parser(head) & 4u) != 0)
	{
		err_flg = add_var_to_env(cont) ? 1 : 0;
		while (head && ft_strcmp(get_str(head), "export"))
			head = head->next;
		if (head)
			set_flag_parser(head, get_flag_parser(head) | 8u);
	}
	else
		check_var_in_env(g_env_vars, cont);
	return (err_flg);
}

int				got_var(const char *start, const char *eq_sign, t_list **cur)
{
	const char	*end;
	char		*cont[2];
	int			err_flg;
	t_list		*head;

	head = *cur;
	end = eq_sign;
	if (*(eq_sign + 1) == 0)
		err_flg = got_var_sub(cont, cur);
	else
	{
		while (*end)
			end++;
		cont[1] = ft_calloc(end - eq_sign + 1, sizeof(char));
		err_flg = (cont[1]) ? 0 : 1;
		!err_flg ? ft_strncpy(cont[1], eq_sign + 1, end - eq_sign) : NULL;
	}
	if (err_flg || !(cont[0] = ft_calloc(eq_sign - start + 1, sizeof(char))))
		return (1);
	ft_strncpy(cont[0], start, eq_sign - start);
	export_check(head, cont);
	if (add_var_to_list(&g_loc_vars, cont, 1))
		err_flg = 1;
	return (err_flg + free_str(&cont[0]) + free_str(&cont[1]) ? 1 : 0);
}
