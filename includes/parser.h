/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 13:05:20 by fgavin            #+#    #+#             */
/*   Updated: 2020/08/29 18:54:32 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

# define DELIM_NUM 11

//TODO del this
const char	*stub(const char *start, t_list **list, const char *params);

const char	*got_dollar(const char *start, t_list **list, const char *params);
const char	*got_backslash(const char *start, t_list **list, const char *params);
const char	*got_literal(const char *start,  t_list **list, const char *params);
const char	*got_unit_delimiter(const char *start,  t_list **list, const char *params);
const char	*got_double_delimiter(const char *start,  t_list **list, const char *params);
const char	*got_double_quotes(const char *start, t_list **list, const char *params);
const char	*got_sing_quote(const char *start, t_list **list, const char *params);
const char	*got_space(const char *start, t_list **list, const char *params);
t_list		*parser(const char *str);
t_list		*create_node(const char *data, size_t len, unsigned flag);
int			push_node(t_list **list, t_list *new_node);
int			is_delim(const char *str, const char *eot);
char		**set_params(int key, char *eot);
void		set_flag_parser(t_list *node, unsigned flag);
unsigned	get_flag_parser(t_list *node);
char		*get_str(t_list *node);
const char	*rec_parser(const char *str, t_list **list, char *eot);
char		*get_var(const char *str);
void		ft_lstreverse(t_list **list);
void		ft_delspaces(t_list **list);
void		del_var_cont(void *content);
char		*got_var(char *start, char *eq_sign, char *params, t_list **env);
int			cr_var_cont(const char *start, const char *eq_sign,
						   const char *end, char **content);//change to static and del from here

typedef struct
{
	int			key;
	int			ign_q;
	char		data[3];
	const char	*(*func) (const char *, t_list **, const char *);
}				t_delims;

static const t_delims	g_delims[DELIM_NUM] = {
		(t_delims){.key = 0, .ign_q = 0, .data = "\\", .func = got_backslash},
		(t_delims){.key = 1, .ign_q = 0, .data = " ", .func = got_space},
		(t_delims){.key = 2, .ign_q = 1, .data = "$", .func = got_dollar},
		(t_delims){.key = 3, .ign_q = 0, .data = ">>", .func = got_double_delimiter},
		(t_delims){.key = 4, .ign_q = 0, .data = "<>", .func = got_double_delimiter},
		(t_delims){.key = 5, .ign_q = 0, .data = "<", .func = got_unit_delimiter},
		(t_delims){.key = 6, .ign_q = 0, .data = ">", .func = got_unit_delimiter},
		(t_delims){.key = 7, .ign_q = 0, .data = "|", .func = got_unit_delimiter},
		(t_delims){.key = 8, .ign_q = 0, .data = ";", .func = got_unit_delimiter},
		(t_delims){.key = 9, .ign_q = 0, .data = "\"", .func = got_double_quotes},
		(t_delims){.key = 10, .ign_q = 0, .data = "\'", .func = got_sing_quote},
		//(t_delims){.key = , .ign_q = , .data = "", .func = stub},
};

#endif
