/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 03:05:53 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/12 03:06:41 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		del_var_cont(void *content)
{
	char	**cont;

	cont = content;
	free(cont[0]);
	cont[0] = NULL;
	free(cont[1]);
	cont[1] = NULL;
	free(cont);
}
