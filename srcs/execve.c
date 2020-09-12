/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 02:42:01 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/12 02:43:45 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <dirent.h>
#include "libft.h"
#include "minishell.h"
#include <string.h>

static int	check_file_current_dir(char *str)
{
	struct stat		stats;

	if (stat(str, &stats))
		return (0);
	if (!S_ISREG(stats.st_mode))
		return (0);
	return (1);
}

static int	check_file(char *path, char *file)
{
	DIR				*dir;
	struct dirent	*dir_str;

	if (!(dir = opendir(path)))
		return (0);
	while ((dir_str = readdir(dir)))
	{
		if (!ft_strcmp(dir_str->d_name, file))
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

char		*add_path(char *func)
{
	int				i;
	char			*ret;
	char			*tmp;
	char			**paths;

	if (check_file_current_dir(func))
		return (func);
	i = -1;
	paths = (char **)ft_calloc(sizeof(char *), 20);
	while (g_env_vars[++i])
	{
		if (!ft_strncmp(g_env_vars[i], "PATH=", 5))
			paths = ft_split(&g_env_vars[i][5], ':');
	}
	i = -1;
	while (paths[++i])
	{
		if ((check_file(paths[i], func)))
		{
			tmp = ft_strjoin("/", func);
			ret = ft_strjoin(paths[i], tmp);
			free(tmp);
			return (free_args(&paths) + ret);
		}
	}
	free_args(&paths);
	return (NULL);
}
