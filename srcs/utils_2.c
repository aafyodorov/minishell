/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 00:10:55 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/19 03:01:11 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int		show_prompt(void)
{
	char		*homepath;
	int			size;

	homepath = NULL;
	size = 256;
	while (!(homepath = getcwd(NULL, size)))
	{
		size *= 2;
		if (size >= INT_MAX / 2)
		{
			ft_putendl_fd("Error! No memory for path to directory!", 2);
			return (1);
		}
	}
	ft_printf("%sminishell%s:%s~%s%s$ ", GREEN, RESET, BLUE, homepath,
		RESET);
	free(homepath);
	return (0);
}

int		read_stdin(t_buf *buf, char **input)
{
	char			ch;
	int				read_b;
	int				readed;

	ch = 0;
	read_b = 0;
	while (((readed = read(0, &ch, 1)) && ch != 10) || (!readed && buf->i))
	{
		if ((!readed && buf->i))
			continue;
		if (add_to_buf(buf, ch, input))
			return (1);
		read_b = 1;
	}
	if (!*input && ch == 10)
		read_b = -1;
	return (read_b);
}

int		print_error(char *message, int exit_code)
{
	ft_putendl_fd(message, 2);
	errno = 0;
	return (exit_code);
}

int		ft_empty(char **args)
{
	(void)args;
	return (0);
}

int		redirect_1(t_list *parse)
{
	if (parse && is_redirect(get_str(parse), get_flag_p(parse)))
		return (print_error("minishell: syntax error", 2));
	return (0);
}
