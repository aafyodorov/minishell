/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2020/09/15 17:57:34 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/15 17:58:23 by pdemocri         ###   ########.fr       */
=======
/*   Created: 2020/09/15 05:05:18 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/15 05:08:35 by pdemocri         ###   ########.fr       */
>>>>>>> 8ac25586dd68fe01be4fbb9966ced4184e7f68e8
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include "parser.h"
# include "libftprintf.h"
# include "libft.h"
# include "arr_buf.h"
# include "redirect.h"

# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"

int			g_exit_status;
int			g_fork_flag;
char		**g_env_vars;
t_list		*g_loc_vars;

int			ft_echo(char **args);
int			ft_cd(char **args);
int			ft_pwd(char **args);
int			ft_export(char **args);
int			ft_unset(char **args);
int			ft_env(char **args);
int			ft_exit(char **args);

int			ft_strlenbuf(char **buf);
int			get_envs(char **envp, char ***g_env_vars);
char		**get_args_str(t_list *parse);
void		change_underscores(char *func, char **args);
char		*add_path(char *func);

void		signal_handler(void);

int			free_str(char **str);
int			free_args(char ***args);

int			is_func(char *str);
int			is_redirect(char *str);
int			check_redirect(t_list **parse);

void		ctrl_d(void);
int			show_prompt();
int			read_stdin(t_buf *buf, char **input);
int			loop_read();
int			print_error(char *message, int exit_code);

#endif
