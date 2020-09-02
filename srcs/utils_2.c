/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 00:10:55 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/03 00:22:18 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		show_prompt()
{
	static int	size = 1024;
	unsigned	iter;
	char		homepath[size];

	iter = 0;
	while (!getcwd(homepath, size))
	{
		iter++;
		size *= 2;
		if (iter > 15)
		{
			ft_putendl_fd("Go to hell with yours super long string!", 2);
			return (1);
		}
	}
	ft_printf("%sminishell%s:%s~%s%s$ ", GREEN, RESET, BLUE, homepath,
		RESET);
	return (0);
}

int		read_stdin(t_buf *buf, char **input)
{
	static int		isFirstCall = 0;
	char			ch;
	int 			read_b;

	read_b = 0;
	while (read(0, &ch, 1) && ch != 10)
	{
		if (add_to_buf(buf, ch, input))
			return (1);
		read_b = 1;
	}
	return (read_b);
}
