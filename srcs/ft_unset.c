/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:05:57 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/18 06:07:16 by pdemocri         ###   ########.fr       */
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
		free(tmp);
	}
}

void		change_underscores(char *func, char **args)
{
	int		i;
	char	*tmp;

	tmp = args[0] ? args[ft_strlenbuf(args) - 1] : func;
	i = 0;
	while (g_env_vars[i] && ft_strncmp(g_env_vars[i], "_=", 2))
		i++;
	free(g_env_vars[i]);
	if (!(g_env_vars[i] = ft_strjoin("_=", tmp)) && errno)
		print_error(strerror(i), 1);
}

int			ft_unset(char **args)
{
	int		i;
	int		j;
	int		len;

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
