/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_del_spaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:04:42 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/12 22:05:13 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	skip_spaces(t_list **list)
{
	t_list	*tmp;

	while (*list && !ft_strcmp(get_str(*list), " "))
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}

void		ft_delspaces(t_list **list)
{
	int		flag;
	t_list *prev;
	t_list *curr;

	skip_spaces(list);
	flag = 0;
	prev = NULL;
	curr = *list;
	while (curr)
	{
		if ((!prev || is_redirect(get_str(prev))) &&
			!ft_strcmp(get_str(curr), "echo"))
			flag = 1;
		if (curr && is_redirect(get_str(curr)))
			flag = 0;
		if ((!flag || (prev && !ft_strcmp(get_str(prev), "echo"))) && curr &&
			!ft_strcmp(get_str(curr), " "))
		{
			prev->next = curr->next;
			free(curr);
			curr = prev->next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}