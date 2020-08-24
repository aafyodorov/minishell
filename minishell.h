#ifndef MINISHELL_H
# define MINISHELL_H

#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

<<<<<<< HEAD
char		**g_env;
=======
typedef struct 		s_env
{
	char			*env;
	struct s_env	*next;
}					t_env;


t_env		*g_env;
char		*g_res;
>>>>>>> 402b7099ea754a2d9a234393308d1721431d8bf7

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