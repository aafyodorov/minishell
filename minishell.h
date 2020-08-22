#ifndef MINISHELL_H
# define MINISHELL_H

#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m" 

char		**g_env;char		*g_res;

int			ft_echo(char *str);
int			ft_cd(char *str);
int			ft_pwd(char *str);
int			ft_export(char *str);
int			ft_unset(char *str);
int			ft_env(char *str);
int			ft_exit(char *str);

int			free_str(char **str);
int			free_args(char ***args);

int			check_func(char *str);
int			check_args(char *str);
int			check_operator(char *str);

#endif