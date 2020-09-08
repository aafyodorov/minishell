/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:56 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/08 19:33:22 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int		is_func(char *str)
{
	const char	*funcs_str[8] = {NULL,
								"echo",
								"cd",
								"pwd",
								"export",
								"unset",
								"env",
								"exit"};
	int			i;

	i = 0;
	while (++i < 8)
		if (!ft_strcmp(funcs_str[i], str))
			return (i);
	return (0);
}

int		is_redirect(char *str)
{
	int			i;
	const char	redir[6][3] = {"", ";", "|", ">", ">>", "<"};

	i = 0;
	while (++i < 6)
	{
		if (!ft_strcmp(str, redir[i]))
			return (i);
	}
	return (0);
}

int		next_redirect(t_list *parse)
{
	int		i;

	i = 0;
	while (parse && !(i = is_redirect(get_str(parse))))
		parse = parse->next;
	return (i);
}

void	check_redirect(t_list **parse)
{
	const void		(*funcs[6])(t_list *) = {NULL,
										redirect_1,
										redirect_2,
										redirect_3
													};
										// redirect_4,
										// redirect_5};
	const int		pipe_status = next_redirect(*parse);

	if (pipe_status)
		funcs[pipe_status](parse);
	if (pipe_status >= 3)
	{
		while (*parse && !is_redirect(get_str(*parse)))
			*parse = (*parse)->next;
		*parse = (*parse)->next;
	}
	g_pipe_status = pipe_status;
}