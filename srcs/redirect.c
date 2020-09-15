/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:03:14 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/15 18:39:26 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "redirect.h"

int			redirect_2(t_list *parse)
{
	if ((parse = NULL))
		return (0);
	if (pipe(g_pipe) == -1)
		return (errno);
	return (0);
}

static char	*get_filename(t_list *parse)
{
	char		*res;

	res = NULL;
	while (parse && !(is_redirect(get_str(parse))))
		parse = parse->next;
	if (parse->next)
		res = get_str(parse->next);
	return (res);
}

int			redirect_3(t_list *parse)
{
	const char	*filename = get_filename(parse);

	if (!filename)
		return (print_error("echo: syntax error", 2));
	close(1);
	g_pipe[1] = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (g_pipe[1] < 0)
		return (print_error(strerror(errno), 1));
	return (0);
}

int			redirect_4(t_list *parse)
{
	const char	*filename = get_filename(parse);

	if (!filename)
	{
		g_exit_status = 2;
		ft_printf("echo: syntax error");
		return (2);
	}
	close(1);
	g_pipe[1] = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (g_pipe[1] < 0)
		return (print_error(strerror(errno), 1));
	return (0);
}

int			redirect_5(t_list *parse)
{
	const char	*filename = get_filename(parse);

	if (!filename)
		return (print_error("echo: syntax error", 2));
	close(0);
	g_pipe[0] = open(filename, O_RDONLY);
	if (g_pipe[0] < 0)
		return (print_error(strerror(errno), 1));
	return (0);
}
