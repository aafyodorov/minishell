/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:48 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/15 21:05:12 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"
#include "minishell.h"

int	ft_env(char **args)
{
	int			i;

	i = 0;
	if (args[0])
		return (print_error("Invalid argument\n", 127));
	while (g_env_vars[i])
		ft_printf("%s\n", g_env_vars[i++]);
	return (0);
}

int	get_envs(char **envp, char ***g_env_vars)
{
	int			i;

	i = ft_strlenbuf(envp);
	if (!(*g_env_vars = (char **)ft_calloc(sizeof(char *), i + 100)))
		return (1);
	i = 0;
	while (envp[i])
	{
		if (!((*g_env_vars)[i] = (char *)malloc(ft_strlen(envp[i]) + 1)))
			return (1);
		ft_strcpy((*g_env_vars)[i], envp[i]);
		i++;
	}
	return (0);
}
