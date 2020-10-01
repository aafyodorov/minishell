/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:56 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/19 02:59:49 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "redirect.h"

int			is_func(char *str)
{
	const char	*funcs_str[9] = {NULL,
								"echo",
								"cd",
								"pwd",
								"export",
								"unset",
								"env",
								"exit",
								"\t"};
	int			i;

	if (!str)
		return (8);
	i = 0;
	while (++i < 9)
		if (!ft_strcmp(funcs_str[i], str))
			return (i);
	return (0);
}

int			is_redirect(char *str, int flag)
{
	int			i;
	const char	redir[6][3] = {"", ";", "|", ">", ">>", "<"};

	i = 0;
	while (++i < 6)
	{
		if (!ft_strcmp(str, redir[i]) && (flag & 32))
			return (i);
	}
	return (0);
}

int			next_redirect(t_list *parse)
{
	int		i;

	i = 0;
	while (parse && !(i = is_redirect(get_str(parse), get_flag_p(parse))))
		parse = parse->next;
	return (i);
}

static void	skip_redirect(t_list **parse)
{
	char *tmp;

	tmp = NULL;
	while (*parse && !is_redirect(get_str(*parse), get_flag_p(*parse)))
	{
		tmp = get_str(*parse);
		*parse = (*parse)->next;
	}
	if (*parse)
	{
		tmp = get_str(*parse);
		*parse = (*parse)->next;
	}
}

int			check_redirect(t_list **parse)
{
	int				ret;
	const int		pipe_status = next_redirect(*parse);

	errno = 0;
	ret = 0;
	if (pipe_status)
		ret = g_funcs_red[pipe_status](*parse);
	if (pipe_status >= 3)
	{
		g_pipe_prev = pipe_status;
		skip_redirect(parse);
		check_redirect(parse);
	}
	if (!pipe_status && g_pipe_prev < 3)
		ret = open_stdin_stdout();
	g_exit_status = ret ? ret : g_exit_status;
	g_pipe_next = pipe_status;
	return (ret);
}
