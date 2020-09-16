/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 17:57:37 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/16 02:52:17 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "minishell.h"

# define DELIM_NUM 11

const char		*got_dollar(const char *start, t_list **list,
						const char *params);
const char		*got_backslash(const char *start, t_list **list,
							const char *params);
const char		*got_literal(const char *start, t_list **list,
						const char *params);
const char		*got_unit_delimiter(const char *start, t_list **list,
								const char *params);
const char		*got_double_delimiter(const char *start, t_list **list,
									const char *params);
const char		*got_double_quotes(const char *start, t_list **list,
								const char *params);
const char		*got_sing_quote(const char *start, t_list **list,
							const char *params);
const char		*got_space(const char *start, t_list **list,
							const char *params);
t_list			*parser(const char *str);
t_list			*create_node(const char *data, size_t len, unsigned flag,
					t_list *head);
int				push_node(t_list **list, t_list *new_node);
int				is_delim(const char *str, const char *eot);
char			**set_params(int key, char *eot);
void			set_flag_parser(t_list *node, unsigned flag);
unsigned		get_flag_parser(t_list *node);
char			*get_str(t_list *node);
const char		*rec_parser(const char *str, t_list **list, char *eot);
char			*get_var(const char *str);
void			ft_lstreverse(t_list **list);
void			ft_delspace(t_list **list);
void			del_redirect_spaces(t_list **list);
void			del_var_cont(void *content);
char			*got_var(const char *start, const char *eq_sign,
				const char *params, t_list *head);
int				cr_var_cont(const char *start, const char *eq_sign,
					const char *end, char **content);
t_list			*find_elem(t_list *list, char *key);

typedef struct
{
	int			key;
	int			ign_q;
	char		data[3];
	const char	*(*func) (const char *, t_list **, const char *);
}				t_delims;

static const t_delims	g_delims[DELIM_NUM] = {
		(t_delims){.ign_q = 0, .data = "\\", .func = got_backslash},
		(t_delims){.ign_q = 0, .data = " ", .func = got_space},
		(t_delims){.ign_q = 0, .data = "\t", .func = got_space},
		(t_delims){.ign_q = 1, .data = "$", .func = got_dollar},
		(t_delims){.ign_q = 0, .data = ">>", .func = got_double_delimiter},
		(t_delims){.ign_q = 0, .data = "<", .func = got_unit_delimiter},
		(t_delims){.ign_q = 0, .data = ">", .func = got_unit_delimiter},
		(t_delims){.ign_q = 0, .data = "|", .func = got_unit_delimiter},
		(t_delims){.ign_q = 0, .data = ";", .func = got_unit_delimiter},
		(t_delims){.ign_q = 0, .data = "\"", .func = got_double_quotes},
		(t_delims){.ign_q = 0, .data = "\'", .func = got_sing_quote}
};

#endif
