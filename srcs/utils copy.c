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

static int		is_empty_export(t_list *parse)
{
	return ((get_flag_parser(parse) & 8u) &&
				(!parse->next ||
				(parse->next &&
					is_redirect(get_str(parse->next)))));
}

char			**get_args_str(t_list *parse)
{
	int			i;
	int			len;
	char		**args;
	char		*tmp[2];

	len = str_args_len(parse);
	args = (char **)ft_calloc(len + 10, sizeof(char *));
	i = 0;
	while (parse && i < len)
	{
		tmp[0] = args[i];
		if (subst_var(&parse, &args[i], &i))
			continue;
		tmp[1] = ft_strdup_arg(get_str(parse), get_flag_parser(parse), g_env_vars);
		args[i] = tmp[0] ? ft_strjoin(tmp[0], tmp[1]) : ft_strdup(tmp[1]);
		if (!(get_flag_parser(parse) & 1u))
			i++;
		if (is_empty_export(parse))
			args[i++] = ft_strdup(" ");
		(void)(free_str(&tmp[1]) + free_str(&tmp[0]));
		parse = parse->next;
	}
	return (args);
}
