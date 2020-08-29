/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 06:08:05 by pdemocri          #+#    #+#             */
/*   Updated: 2020/08/29 03:03:29 by pdemocri         ###   ########.fr       */
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

# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"

int			g_pipe[2];
int			g_fd[5];
int			g_exit_status;

int			ft_echo(char **args, char **env);
int			ft_cd(char **args, char **env);
int			ft_pwd(char **args, char **env);
int			ft_export(char **args, char **env);
int			ft_unset(char **args, char **env);
int			ft_env(char **args, char **env);
int			ft_exit(char **args, char **env);

int			ft_strlenbuf(char **buf);
char		**get_envs(char **envp);
char		**get_args_str(t_list *parse, char **env);
void		change_underscores(char *func, char **args, char **env);
char		*add_path(char *func, char **env);

void		close_stdin_stdout(char *file);
void		open_stdin_stdout(void);

void		signal_handler(void);

int			free_str(char **str);
int			free_args(char ***args);

int			is_func(char *str);
int			is_redirect(char *str);
void		check_redirect(t_list *parse);

#endif
