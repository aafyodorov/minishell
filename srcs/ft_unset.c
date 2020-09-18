/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:05:57 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/19 02:49:03 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "minishell.h"
#include "parser.h"

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

void		del_loc_var(t_list **loc_vars, char *var)
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = *loc_vars;
	while (curr)
	{
		if (!ft_strcmp(((char **)(curr->content))[0], var))
		{
			if (prev)
				prev->next = curr->next;
			else
				g_loc_vars = curr->next;
			del_var_cont(curr->content);
			free(curr);
			curr = NULL;
			curr = prev ? prev->next : NULL;
			break ;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

int			ft_unset(char **args)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	if (!ft_strncmp(args[i], "_", 1))
	{
		change_underscores("env", args);
		return (0);
	}
	while (args[++i])
	{
		j = 0;
		len = ft_strlen(args[i]);
		while (g_env_vars[j])
		{
			if (!ft_strncmp(args[i], g_env_vars[j], len))
				delete_var(&g_env_vars, j);
			j++;
		}
		del_loc_var(&g_loc_vars, args[i]);
	}
	return (0);
}
