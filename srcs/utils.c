/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:07:22 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/26 21:24:16 by fgavin           ###   ########.fr       */
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
	char		**args;
	char		*tmp[3];
	int			echo_flag;

	init_args(&args, parse, &i, &tmp[2]);
	echo_flag = get_command(&parse, &args[0], &i);
	while (parse && !is_redirect(get_str(parse), get_flag_p(parse)))
	{
		tmp[0] = args[i];
		if ((skip_spaces(&parse, &i, echo_flag, args[i]) ||
				(echo_flag != 1 && subst_var(&parse, &args[i], &i))))
			continue;
		tmp[1] = ft_strdup_arg(get_str(parse),
				get_flag_p(parse), g_env_vars);
		if (!(get_flag_p(parse) & 1) && (echo_flag == 1 && tmp[1] &&
				!tmp[1][0] && uninitialized(&parse, args, i, tmp)))
			continue;
		args[i] = tmp[0] ? ft_strjoin(tmp[0], tmp[1]) : ft_strdup(tmp[1]);
		(void)(free_str(&tmp[1]) + free_str(&tmp[0]));
		tmp[2] = get_flag_p(parse) & 1 ? (void *)0x1 : NULL;
		parse = parse->next;
	}
	return (args);
}
