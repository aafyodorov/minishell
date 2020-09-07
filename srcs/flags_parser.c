/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 15:19:24 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/28 21:51:34 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		set_flag_parser(t_list *node, unsigned flag)
{
	unsigned	**cont;

	cont = node->content;
	cont[0][0] = flag;
}

unsigned	get_flag_parser(t_list *node)
{
	return (((unsigned **)(node->content))[0][0]);
}

char		*get_str(t_list *node)
{
	return (((char **)(node->content))[1]);
}
