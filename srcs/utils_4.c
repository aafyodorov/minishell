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
	*parse = NULL;
	g_exit_status = print_error("minishell: syntax error", 2);
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
				return (syntax_error(parse));
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

static int	str_args_len(t_list *parse)
{
	int			len;

	len = 0;
	while ((parse && !is_redirect(get_str(parse), get_flag_p(parse))))
	{
		len++;
		parse = parse->next;
	}
	return (len);
}

void		init_args(char ***args, t_list *parse, int *i, char **buf)
{
	*args = (char **)ft_calloc(str_args_len(parse) + 10, sizeof(char *));
	*i = 0;
	*buf = NULL;
}
