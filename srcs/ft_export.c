/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:05:46 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/15 03:33:18 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static void	insertion_sort(char ***array, int size)
{
	int		i;
	int		i_tmp;
	char	*str_tmp;

	i = 1;
	while (i < size)
	{
		if (ft_strcmp((*array)[i - 1], (*array)[i]) > 0)
		{
			str_tmp = (*array)[i];
			i_tmp = i;
			while (i_tmp > 0 && ft_strcmp((*array)[i_tmp - 1], str_tmp) > 0)
			{
				(*array)[i_tmp] = (*array)[i_tmp - 1];
				i_tmp--;
			}
			(*array)[i_tmp] = str_tmp;
		}
		i++;
	}
}

static int	print_env(void)
{
	int		i;
	int		size;
	char	**sorted_vars;

	i = 0;
	size = ft_strlenbuf(g_env_vars);
	get_envs(g_env_vars, &sorted_vars);
	insertion_sort(&sorted_vars, size);
	while (i < size)
		ft_printf("declare -x %s\n", sorted_vars[i++]);
	free_args(&sorted_vars);
	return (0);
}

static char	*find_env_var(char **var_list, char *str)
{
	int		i;

	i = 0;
	while (var_list[i])
	{
		if (!ft_strncmp(var_list[i], str, ft_strlen(str)) &&
			var_list[i][ft_strlen(str)] == '=')
			return (var_list[i]);
		i++;
	}
	return (NULL);
}

static char	*find_loc_var(t_list *var_list, char *str)
{
	char	**content;
	char	*tmp;
	char	*exp;

	while (var_list)
	{
		content = var_list->content;
		if (!ft_strcmp(content[0], str))
		{
			if (!(tmp = ft_strjoin(content[0], "=")) ||
				!(exp = ft_strjoin(tmp, content[1])))
			{
				print_error(strerror(errno), 1);
				return (NULL);
			}
			free(tmp);
			return (exp);
		}
		var_list = var_list->next;
	}
	return (NULL);
}

int			ft_export(char **args)
{
	int		i;
	char	*exp;
	char	*tmp;

	exp = NULL;
	i = -1;
	if (!args[0])
		return (print_env());
	while (args[++i])
	{
		exp = find_env_var(g_env_vars, args[i]);
		if (exp)
			continue;
		tmp = find_loc_var(g_loc_vars, args[i]);
		if (tmp)
			g_env_vars[ft_strlenbuf(g_env_vars)] = tmp;
	}
	return (0);
}
