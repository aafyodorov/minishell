/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 15:19:24 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/28 15:19:24 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		set_flag(t_list *node, unsigned flag)
{
	unsigned	**cont;

	cont = node->content;
	cont[0][0] = flag;
}

unsigned	get_flag(t_list *node)
{
	return (((unsigned **)(node->content))[0][0]);
}

char		*get_str(t_list *node)
{
	return (((char **)(node->content))[1]);
}
