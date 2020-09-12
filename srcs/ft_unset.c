/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 02:52:07 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/12 02:52:09 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "minishell.h"

static void	delete_var(char ***env, int j)
{
	char	*tmp;

	if (j == ft_strlenbuf(*env) - 1)
	{
		free((*env)[j]);
		(*env)[j] = NULL;
	}
	else
	{
		tmp = (*env)[j];
		while ((*env)[j])
		{
			(*env)[j] = (*env)[j + 1];
			j++;
		}
		free((*env)[j]);
	}
}

void		change_underscores(char *func, char **args)
{
	int		i;
	char	*tmp;

	tmp = args[0] ? args[ft_strlenbuf(args) - 1] : func;
	i = 0;
	while (ft_strncmp(g_env_vars[i], "_=", 2))
		i++;
	free(g_env_vars[i]);
	g_env_vars[i] = ft_strjoin("_=", tmp);
}

int			ft_unset(char **args) //////////не работает!!!
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	if (!ft_strncmp(args[i], "_", 1))
	{
		change_underscores("env", args);
		return (0);
	}
	while (args[i])
	{
		j = 0;
		len = ft_strlen(args[i]);
		while (g_env_vars[j])
		{
			if (!ft_strncmp(args[i], g_env_vars[j], len))
				delete_var(&g_env_vars, j);
			j++;
		}
		i++;
	}
	return (0);
}
