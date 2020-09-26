/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:07:22 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/26 21:31:54 by fgavin           ###   ########.fr       */
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
	echo_flag = (*parse && !ft_strcmp("export", get_str(*parse))) ? 2 :
			echo_flag;
	while (*parse && !is_redirect(get_str(*parse)) &&
			ft_strcmp(" ", get_str(*parse)))
	{
		tmp[0] = *args;
		if (subst_var(parse, args, i))
			return (2);
		tmp[1] = ft_strdup_arg(get_str(*parse),
				get_flag_parser(*parse), g_env_vars);
		*args = *args ? ft_strjoin(*args, tmp[1]) : ft_strdup(tmp[1]);
		(void)(free_str(&tmp[0]) + free_str(&tmp[1]));
		if (*parse && is_empty_export(*parse))
			args[++(*i)] = ft_strdup(" ");
		*parse = (*parse)->next;
	}
	*parse = (*parse && !is_redirect(get_str(*parse))) ?
			(*parse)->next : *parse;
	(*i)++;
	echo_n(parse, args, i, echo_flag);
	return (echo_flag);
}

int			skip_spaces(t_list **parse, int *i, int echo_flag, char *args)
{
	if (!echo_flag && !ft_strcmp(" ", get_str(*parse)))
	{
		(*i)++;
		*parse = (*parse)->next;
		return (1);
	}
	else if (!args && !ft_strcmp(" ", get_str(*parse)))
	{
		*parse = (*parse)->next;
		return (1);
	}
	return (0);
}

/*
** 1 in first byte free str1
** 1 in secons byte free str2
*/

char		*ft_strjoin_free(char *str1, char *str2, unsigned flag)
{
	char		*res;

	res = NULL;
	if (str1 && str2)
		res = ft_strjoin(str1, str2);
	if (flag & 1u)
		free(str1);
	if (flag & 2u)
		free(str2);
	return (res);
}

int			uninitialized(t_list **parse, char **args, int i, char **tmp)
{
	*parse = (*parse)->next;
	if (i && args[i] && args[i][ft_strlen(args[i]) - 1] == ' ')
		args[i][ft_strlen(args[i]) - 1] = '\0';
	if (*parse && !ft_strcmp(" ", get_str(*parse)) && !(*parse)->next)
		*parse = (*parse)->next;
	free_str(tmp);
	return (1);
}
