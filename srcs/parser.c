/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 13:01:23 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/15 23:35:46 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO check Norm libft!!!

#include "parser.h"

const char		*get_next_part(const char *str, int *key, t_list **list,
		char *eot)
{
	const char	*ptr;

	*key = is_delim(str, eot);
	ptr = NULL;
	if (*key != -1)
		ptr = g_delims[*key].func(str, list, eot);
	else
		ptr = got_literal(str, list, eot);
	return (ptr);
}

const char		*rec_parser(const char *str, t_list **list, char *eot)
{
	const char	*ptr;
	int			key;

	while (*str != *eot)
	{
		ptr = NULL;
		key = -1;
		if (!(ptr = get_next_part(str, &key, list, eot)))
		{
			ft_lstclear(list, free);
			return (NULL);
		}
		str = ptr;
	}
	str += (*str == *eot && *eot) ? 1 : 0;
	return (str);
}

t_list			*parser(const char *str)
{
	t_list		*list;

	list = NULL;
	if (!rec_parser(str, &list, ""))
		return (NULL);

	 t_list *t_list = list;
//	while(t_list) {
//		printf("'%s'\t", get_str(t_list));
//		t_list = t_list->next;
//	}
//	printf("\n________________\n");

	del_redirect_spaces(&list);
	ft_lstreverse(&list);
	ft_delspace(&list);

//		t_list = list;
//	while(t_list) {
//		ft_printf("flag: '%d'\t data: '%s'\n", get_flag_parser(t_list), get_str(t_list));
//		t_list = t_list->next;
//	}
//	ft_printf("\n________________\n");

	return (list);
}
