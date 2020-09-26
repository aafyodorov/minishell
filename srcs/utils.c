/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:07:22 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/19 22:20:28 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"

int			ft_strlenbuf(char **buf)
{
	int			i;

	i = 0;
	while (buf[i])
		i++;
	return (i);
}

static int	str_args_len(t_list *parse)
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

char		*ft_strdup_arg(char *str, unsigned flag, char **env)
{
	int			i;
	const int	len = ft_strlen(str);

	i = 0;
	if (!ft_strcmp(str, "?") && flag & 2u)
		return (ft_itoa(g_exit_status));
	if (flag & 2u)
	{
		while (env[i])
		{
			if (!ft_strncmp(str, env[i], len) && env[i][len] == '=')
				return (ft_strdup(&env[i][len + 1]));
			if (find_elem(g_loc_vars, str))
				return (ft_strdup(get_str(find_elem(g_loc_vars, str))));
			i++;
		}
		return (ft_strdup(""));
	}
	return (strdup(str));
}

char		**get_args_str(t_list *parse)
{
	int			i;
	int			len;
	char		**args;
	char		*tmp[2];
	int			echo_flag;

	len = str_args_len(parse);
	args = (char **)ft_calloc(len + 10, sizeof(char *));
	i = 0;
	echo_flag = get_command(&parse, &args[0], &i);
	while (parse && !is_redirect(get_str(parse)))
	{
		if (skip_spaces(&parse, &i, echo_flag))
			continue;
		tmp[0] = args[i];
		if (!echo_flag && subst_var(&parse, &args[i], &i))
			continue;
		tmp[1] = ft_strdup_arg(get_str(parse),
				get_flag_parser(parse), g_env_vars);
		if (echo_flag && tmp[1] && !tmp[1][0] &&
				uninitialized(&parse, args, i))
			continue;
		args[i] = tmp[0] ? ft_strjoin(tmp[0], tmp[1]) : ft_strdup(tmp[1]);
		(void)(free_str(&tmp[1]) + free_str(&tmp[0]));
		parse = parse->next;
	}
	return (args);
}
