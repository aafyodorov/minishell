/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:56 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/03 22:21:37 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "redirect.h"

int	is_func(char *str)
{
	const char	*funcs_str[7] = {"echo",
								"cd",
								"pwd",
								"export",
								"unset",
								"env",
								"exit"};
	int			i;

	i = 0;
	while (i < 7)
		if (!ft_strcmp(funcs_str[i++], str))
			return (i - 1);
	return (-1);
}

int	is_redirect(char *str)
{
	int			i;
	const char	*redirects[6] = {" ", ";", "|", ">", ">>", "<"};

	i = 0;
	while (++i < 6)
	{
		if (!ft_strcmp(redirects[i], str))
			return (i);
	}
	return (0);
}

/**
 * 0 - not redirect
 * 1 - ;
 * 2 - |
 * 3 - >
 * 4 - >>
 * 5 - <
**/
void	check_redirect(t_list *parse)
{
	const void	(*funcs[6])(void) = {NULL,
										redirect_1,
										redirect_2,
										redirect_3,
										redirect_4,
										redirect_5};
	const void	(*close_funcs[6])(void) = {NULL,
										redirect_1_close,
										redirect_2_close,
										redirect_3_close,
										redirect_4_close,
										redirect_5_close};
	if (g_pipe_status[1])										// если этого был пайп, то возвращаем stdin stdout
		close_funcs[g_pipe_status[1]];
	while (parse && !is_redirect(get_str(parse)))
		parse = parse->next;
	if (parse && (g_pipe_status[0] = is_redirect(get_str(parse))))
		funcs[g_pipe_status[0]]();
}