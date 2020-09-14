/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 13:01:23 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/14 20:41:46 by pdemocri         ###   ########.fr       */
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

static void		del_lead_spaces(t_list **list) {
	t_list		*tmp;
	while (*list && !(ft_strcmp(get_str(*list), " ")))
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
}

static void		ft_delspace(t_list **list)
{
	int			flag;
	t_list		*prev;
	t_list		*curr;

	flag = 0;
	prev = NULL;
	del_lead_spaces(list);
	curr = *list;
	while (curr)
	{
		if ((!prev || is_redirect(get_str(prev))) &&
			!ft_strcmp(get_str(curr), "echo"))
			flag = 1;
		if (curr->content && is_redirect(get_str(curr)))
			flag = 0;
		if ((!flag || (prev && !ft_strcmp(get_str(prev), "echo"))) &&
			!ft_strcmp(get_str(curr), " "))
		{
			prev->next = curr->next;
			free(curr->content);
			free(curr);
			curr = NULL;
			curr = prev->next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

static void		del_redirect_spaces(t_list **list)
{
	t_list		*tmp;
	t_list		*start;

	start = *list;
	while (*list)
	{
		//printf("%s\n", get_str(*list));
		if (is_redirect(get_str(*list)) && (*list)->next &&
			!ft_strcmp(get_str((*list)->next), " ") &&
			!(get_flag_parser((*list)->next) & 1u))
		{
			tmp = (*list)->next->next;
			free((*list)->next->content);
			free((*list)->next);
			(*list)->next = tmp;
		}
		else
			*list = (*list)->next;
	}
	*list = start;
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

//	t_list = list;
//	while(t_list) {
//		printf("'%s'\t", get_str(t_list));
//		t_list = t_list->next;
//	}
//	printf("\n________________\n");

	ft_lstreverse(&list);
	ft_delspace(&list);
	return (list);
}
