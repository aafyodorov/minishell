/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 00:10:55 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/03 23:23:58 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int		show_prompt()
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
	int 			read_b;

	read_b = 0;
	while (read(0, &ch, 1) && ch != 10)
	{
		if (add_to_buf(buf, ch, input))
			return (1);
		read_b = 1;
	}
	if (!*input && ch == 10)
		read_b = -1;
	return (read_b);
}
