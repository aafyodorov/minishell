/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:48 by pdemocri          #+#    #+#             */
/*   Updated: 2020/08/27 03:01:56 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"
#include "minishell.h"

int		ft_env(char **args, char **env)
{
	int			i;

	i = 0;
	if (args[0])
		return (ft_printf("Invalid argument\n"));
	while (env[i])
		ft_printf("%s\n", env[i++]);
	return (0);
}

char	**get_envs(char **envp)
{
	char		**res;
	int			i;

	i = ft_strlenbuf(envp);
	res = (char **)ft_calloc(sizeof(char *), i + 100);
	i = 0;
	while (envp[i])
	{
		res[i] = (char *)malloc(ft_strlen(envp[i]) + 1);
		ft_strcpy(res[i], envp[i]);
		i++;
	}
	return (res);
}