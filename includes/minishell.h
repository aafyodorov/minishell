#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "parser.h"
#include "libftprintf.h"
#include "libft.h"

#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

int			g_exit_status;

int			ft_echo(char **args, char **env, char *ret);
int			ft_cd(char **args, char **env, char *ret);
int			ft_pwd(char **args, char **env, char *ret);
int			ft_export(char **args, char **env, char *ret);
int			ft_unset(char **args, char **env, char *ret);
int			ft_env(char **args, char **env, char *ret);
int			ft_exit(char **args, char **env, char *ret);

int			ft_strlenbuf(char **buf);
char		**get_envs(char **envp);
char	 	**get_args_str(char **parse, int i);
void		change_underscores(char *func, char **args, char **env);
char		*add_path(char *func, char **env);

int			free_str(char **str);
int			free_args(char ***args);

int			check_func(char *str);
int			check_operator(char *str);

#endif