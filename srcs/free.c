/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:24 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/17 03:23:41 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int	free_str(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (0);
}

int	free_args(char ***args)
{
	int		i;

	i = 0;
	while (*args && (*args)[i])
		free((*args)[i++]);
	if (*args)
		free(*args);
	*args = NULL;
	return (0);
}
