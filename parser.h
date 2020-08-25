/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 13:05:20 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/25 14:42:20 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
#include <stdio.h> //delete

# define DELIM_NUM 10

//TODO del this
const char		*stub(const char *start, t_list **list);

const char	*got_backslash(const char *start, t_list **list);
const char	*got_literal(const char *start,  t_list **list);
const char	*got_unit_delimiter(const char *start,  t_list **list);
const char	*got_double_delimiter(const char *start,  t_list **list);
const char	*got_sing_bracket(const char *start, t_list **list);
const char	*got_space(const char *start, t_list **list);
t_list		*parser(const char *str);
t_list		*create_node(const char *data, size_t len);
int			push_node(t_list **list, t_list *new_node);
int			is_delim(const char *str);

typedef struct
{
	int			key;
	char		data[3];
	const char	*(*func) (const char *, t_list **);
}				t_delims;

static t_delims	g_delims[DELIM_NUM] = {
		(t_delims){.key = 0, .data = "\\", .func = got_backslash},
		(t_delims){.key = 1, .data = " ", .func = got_space},
		(t_delims){.key = 2, .data = "$", .func = stub},
		(t_delims){.key = 3, .data = ">>", .func = got_double_delimiter},
		(t_delims){.key = 4, .data = "<", .func = got_unit_delimiter},
		(t_delims){.key = 5, .data = ">", .func = got_unit_delimiter},
		(t_delims){.key = 6, .data = "|", .func = got_unit_delimiter},
		(t_delims){.key = 7, .data = ";", .func = got_unit_delimiter},
		(t_delims){.key = 8, .data = "\"", .func = stub},
		(t_delims){.key = 9, .data = "\'", .func = got_sing_bracket},
		//(t_delims){.key = , .data = "", .func = stub},
};

#endif
