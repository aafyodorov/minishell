/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 02:48:00 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/12 02:48:00 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "libftprintf.h"
#include "minishell.h"

static void	change_oldpwd(void)
{
	int			i;
	int			flag;
	char		buf[1024];

	i = 0;
	flag = 0;
	while (g_env_vars[i])
	{
		if (!ft_strncmp(g_env_vars[i], "OLDPWD", 6))
		{
			free(g_env_vars[i]);
			g_env_vars[i] = ft_strjoin("OLDPWD=", getcwd(buf, 1024));
			flag = 1;
		}
		i++;
	}
	if (!flag)
		g_env_vars[ft_strlenbuf(g_env_vars)] = ft_strjoin("OLDPWD=", getcwd(buf, 1024));
}

int			ft_cd(char **args)
{
	int			i;
	char		tmp[1024];

	i = ft_strlenbuf(args);
	if (i > 1)
		return (ft_printf("cd: слишком много аргументов\n"));
	change_oldpwd();
	if (i == 0 || !ft_strcmp(args[0], "~"))
	{
		while (ft_strncmp("HOME=", g_env_vars[i], 5))
			i++;
		ft_strcpy(tmp, &g_env_vars[i][5]);
		chdir(tmp);
		return (0);
	}
	if (chdir(args[0]))
		return (ft_printf("%s\n", strerror(errno)));
	return (0);
}