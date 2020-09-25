/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:07:22 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/19 22:20:28 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"

static int	is_empty_export(t_list *parse)
{
	return ((get_flag_parser(parse) & 8u) &&
				(!parse->next ||
				(parse->next &&
					is_redirect(get_str(parse->next)))));
}

int			get_command(t_list **parse, char **args, int *i)
{
	char		*tmp[2];
	int			echo_flag;

	echo_flag = (*parse && !ft_strcmp("echo", get_str(*parse))) ? 1 : 0;
	while (*parse && !is_redirect(get_str(*parse)) &&
			ft_strcmp(" ", get_str(*parse)))
	{
		tmp[0] = *args;
		if (subst_var(parse, args, i))
			break ;
		tmp[1] = ft_strdup_arg(get_str(*parse),
				get_flag_parser(*parse), g_env_vars);
		*args = *args ? ft_strjoin(*args, tmp[1]) : ft_strdup(tmp[1]);
		(void)(free_str(&tmp[0]) + free_str(&tmp[1]));
		if (*parse && is_empty_export(*parse))
			args[++(*i)] = ft_strdup(" ");
		*parse = (*parse)->next;
	}
	*parse = *parse ? (*parse)->next : *parse;
	(*i)++;
	return (echo_flag);
}

int			skip_spaces(t_list **parse, int *i, int echo_flag)
{
	if (!echo_flag && !ft_strcmp(" ", get_str(*parse)))
	{
		*parse = (*parse)->next;
		(*i)++;
		return (1);
	}
	return (0);
}
