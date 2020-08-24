#ifndef MINISHELL_H
# define MINISHELL_H

#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

char		**g_env;

int			ft_echo(char **args, char **env, char *ret);
int			ft_cd(char **args, char **env, char *ret);
int			ft_pwd(char **args, char **env, char *ret);
int			ft_export(char **args, char **env, char *ret);
int			ft_unset(char **args, char **env, char *ret);
int			ft_env(char **args, char **env, char *ret);
int			ft_exit(char **args, char **env, char *ret);

void		get_envs(char **envp);

int			free_str(char **str);
int			free_args(char ***args);
int			free_env(t_env	*env);

int			check_func(char *str);
int			check_args(char *str);
int			check_operator(char *str);

void		get_envs(char **envp);

#endif