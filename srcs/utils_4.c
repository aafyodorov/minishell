/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:07:22 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/26 05:55:52 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"

static void	syntax_error(t_list **parse)
{
	ft_lstclear(parse, free);
	*parse = create_node("echo", ft_strlen("echo"), 0, *parse);
	(*parse)->next = create_node(" ", 1, 0, *parse);
	(*parse)->next->next =
		create_node("minishell: syntax error\n",
		ft_strlen("minishell: syntax error"), 0, *parse);
	g_exit_status = 2;
}

void		check_multiple_redirect(t_list **parse)
{
	int			flag;
	t_list		*list;

	flag = 0;
	list = *parse;
	while (list)
	{
		if (is_redirect(get_str(list), get_flag_p(list)))
		{
			if (flag)
				flag = 0;
			else
			{
				syntax_error(parse);
				return ;
			}
		}
		else
			flag = 1;
		list = list->next;
	}
}

void		echo_n(t_list **parse, char **args, int *i, int echo_flag)
{
	if (echo_flag == 1)
	{
		while (*parse && (!ft_strcmp("-n", get_str(*parse))))
		{
			args[*i] = ft_strdup("-n");
			(*i)++;
			*parse = (*parse)->next;
			*parse = (*parse && !ft_strcmp(" ", get_str(*parse))) ?
							(*parse)->next : *parse;
		}
	}
}
