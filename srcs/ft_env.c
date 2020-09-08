/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:48 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/07 16:26:40 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"
#include "minishell.h"

int		ft_env(char **args)
{
	int			i;

	i = 0;
	if (args[0])
		return (ft_printf("Invalid argument\n"));
	while (g_env_vars[i])
		ft_printf("%s\n", g_env_vars[i++]);
	return (0);
}

void	get_envs(char **envp, char ***g_env_vars)
{
	int			i;

	i = ft_strlenbuf(envp);
	*g_env_vars = (char **)ft_calloc(sizeof(char *), i + 100);
	i = 0;
	while (envp[i])
	{
		(*g_env_vars)[i] = (char *)malloc(ft_strlen(envp[i]) + 1);
		ft_strcpy((*g_env_vars)[i], envp[i]);
		i++;
	}
}