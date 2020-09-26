/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 17:57:34 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/26 05:55:52 by fgavin           ###   ########.fr       */
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

# define ENV_LENGTH 100

int			g_exit_status;
char		**g_env_vars;
char		g_home_path[1024];
t_list		*g_loc_vars;
int			g_fork_flag;
int			g_prompt;

static int	(*g_funcs_red[6])(t_list *) = {
	NULL,
	redirect_1,
	redirect_2,
	redirect_3,
	redirect_4,
	redirect_5};

int			ft_echo(char **args);
int			ft_cd(char **args);
int			ft_pwd(char **args);
int			ft_export(char **args);
int			ft_unset(char **args);
int			ft_env(char **args);
int			ft_exit(char **args);
int			ft_empty(char **args);

int			ft_strlenbuf(char **buf);
int			get_envs(char **envp, char ***g_env_varsz);
char		**get_args_str(t_list *parse);
char		*ft_strdup_arg(char *str, unsigned flag, char **env);
int			get_command(t_list **parse, char **args, int *i);
int			skip_spaces(t_list **parse, int *i, int echo_flag, char *args);
int			uninitialized(t_list **parse, char **args, int i, char **tmp);
void		echo_n(t_list **parse, char **args, int *i, int echo_flag);
void		change_underscores(char *func, char **args);
char		*add_path(char *func);

int			free_str(char **str);
int			free_args(char ***args);

int			is_func(char *str);
int			is_redirect(char *str);
int			check_redirect(t_list **parse);

void		signal_handler(void);
void		ctrl_d(void);
void		ctrl_c(int sig);
int			show_prompt();
int			read_stdin(t_buf *buf, char **input);
int			loop_read();
int			print_error(char *message, int exit_code);
int			find_env_var(char **var_list, char *str);
void		get_home_path(void);
char		*ft_strjoin_free(char *str1, char *str2, unsigned flag);

static int	(*g_funcs[9])(char **) = {
	NULL,
	ft_echo,
	ft_cd,
	ft_pwd,
	ft_export,
	ft_unset,
	ft_env,
	ft_exit,
	ft_empty};

#endif
