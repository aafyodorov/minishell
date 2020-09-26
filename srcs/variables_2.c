/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 03:05:53 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/26 04:07:52 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		del_var_cont(void *content)
{
	char	**cont;

	cont = content;
	free(cont[0]);
	cont[0] = NULL;
	free(cont[1]);
	cont[1] = NULL;
	free(cont);
}

int			cr_var_cont(const char *start, const char *eq_sign,
			const char *end, char **content)
{
	size_t		len_name;
	size_t		len_var;

	len_name = eq_sign - start + 1;
	len_var = end - eq_sign + 1;
	content[0] = ft_calloc(len_name, sizeof(char));
	content[1] = ft_calloc(len_var, sizeof(char));
	if (!content[0] || !content[1])
	{
		free(content[0]);
		free(content[1]);
		return (1);
	}
	ft_strncpy(content[0], start, len_name - 1);
	ft_strncpy(content[1], eq_sign + 1, len_var - 1);
	return (0);
}

int			subst_var(t_list **parse, char **args, int *i)
{
	char		*var_name;
	if (get_flag_parser(*parse) & 16u)
	{
		var_name = get_str(*parse);
		if (!(ft_isalpha(var_name[0]) || var_name[0] == '_'))
			return (0);
		got_var(get_str(*parse), ft_strchr(get_str(*parse), '='), parse);//add error check
		*args = ft_strdup(" ");
		(*i)++;
		*parse = (*parse)->next;
		return (1);
	}
	return (0);
}
