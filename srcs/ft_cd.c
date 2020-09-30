/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:05:28 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/18 05:20:30 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "libftprintf.h"
#include "minishell.h"

void		get_home_path(void)
{
	int			i;

	i = 0;
	while (g_env_vars[i] && ft_strncmp("HOME=", g_env_vars[i], 5))
		i++;
	if (g_env_vars[i])
		ft_strcpy(g_home_path, &g_env_vars[i][5]);
	else
		getcwd(g_home_path, 1024);
}

static int	change_oldpwd(void)
{
	int			i;
	int			len;
	char		buf[1024];

	i = 0;
	while (g_env_vars[i])
	{
		if (!ft_strncmp(g_env_vars[i], "OLDPWD", 6))
		{
			free(g_env_vars[i]);
			g_env_vars[i] = ft_strjoin("OLDPWD=", getcwd(buf, 1024));
			return (g_env_vars[i] == NULL);
		}
		i++;
	}
	len = ft_strlenbuf(g_env_vars);
	g_env_vars[len] = ft_strjoin("OLDPWD=", getcwd(buf, 1024));
	return (g_env_vars[len] == NULL);
}

static int	prev_path(void)
{
	int			i;
	char		tmp[1024];

	i = 0;
	while (g_env_vars[i] && ft_strncmp("OLDPWD=", g_env_vars[i], 7))
		i++;
	if (g_env_vars[i])
		ft_strcpy(tmp, &g_env_vars[i][7]);
	else
		ft_strcpy(tmp, g_home_path);
	return (!chdir(tmp) ? 0 : print_error(strerror(errno), 1));
}

int			ft_cd(char **args)
{
	int			i;
	char		tmp[1024];

	i = ft_strlenbuf(args);
	if (i > 1)
		return (print_error("cd: too many arguments", 1));
	if (i == 1 && !ft_strcmp(args[0], "-"))
		return (prev_path());
	if (change_oldpwd())
		return (print_error(strerror(errno), 1));
	if (i == 0 || !ft_strcmp(args[0], "~"))
	{
		while (g_env_vars[i] && ft_strncmp("HOME=", g_env_vars[i], 5))
			i++;
		if (g_env_vars[i])
			ft_strcpy(tmp, &g_env_vars[i][5]);
		else
			ft_strcpy(tmp, g_home_path);
		return (!chdir(tmp) ? 0 : print_error(strerror(errno), 1));
	}
	return (!chdir(args[0]) ? 0 : print_error(strerror(errno), 1));
}
