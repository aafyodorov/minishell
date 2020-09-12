/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:07:22 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/12 22:07:40 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
=======
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 03:01:42 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/12 03:02:40 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

>>>>>>> 41af8fc1cc432629be1c3ff6fb5f00e3112c0343
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "redirect.h"

int				ft_strlenbuf(char **buf)
{
	int			i;

	i = 0;
	while (buf[i])
		i++;
	return (i);
}

static int		str_args_len(t_list *parse)
{
	int			len;

	len = 0;
	while ((parse && !is_redirect(get_str(parse))))
	{
		len++;
		parse = parse->next;
	}
	return (len);
}

static char		*ft_strdup_arg(char *str, unsigned flag, char **env)
{
	int			i;
	const int	len = ft_strlen(str);
	char		*arg;

	i = 0;
	if (!ft_strcmp(str, "?") && flag == 2)
		arg = ft_itoa(g_exit_status);
	else if (flag & 2u)
	{
		while (env[i])
		{
			if (!ft_strncmp(str, env[i], len) && env[i][len] == '=')
				return (ft_strdup(&env[i][len + 1]));
			if (find_elem(g_loc_vars, str))
				return (ft_strdup(get_str(find_elem(g_loc_vars, str))));
			i++;
		}
	}
	else
		arg = strdup(str);
	return (arg);
}

char			**get_args_str(t_list *parse)
{
	int			i;
	int			len;
	char		**args;
	char		*tmp1;
	char		*tmp2;

	len = str_args_len(parse);
	args = (char **)ft_calloc(len + 10, sizeof(char *));
	i = 0;
	while ((parse && i < len))
	{
		tmp1 = args[i];
		tmp2 = ft_strdup_arg(get_str(parse),
							get_flag_parser(parse), g_env_vars);
		if (!get_flag_parser(parse))
			args[i++] = ft_strdup(tmp2);
		else
			args[i++] = ft_strjoin(tmp1 ? tmp1 : "", tmp2);
		free_str(&tmp1);
		free_str(&tmp2);
		parse = parse->next;
	}
	// if (g_pipe_prev == 2)
	// {
	// 	args[ft_strlenbuf(args)] = get_args_from_pipe();
	// 	dup2(g_fd[0], g_pipe[0]);
	// 	dup2(g_fd[1], g_pipe[1]);
	// }
	return (args);
}
