<<<<<<< HEAD
#include "libftprintf.h"
#include "minishell.h"

int			ft_env(char **args, char **env, char *ret)
{
	int			i;

	i = 0;
	if (args[0] || ret)
		return (ft_printf("Invalid argument\n"));
	while (env[i])
		ft_printf("%s\n", env[i++]);
=======
#include "libft.h"
#include "libftprintf.h"
#include "minishell.h"

int			ft_env(char *str) {
	int			i;
	t_env		*tmp;

	i = 0;
	if (str)
		return (ft_printf("Invalid argument\n"));
	tmp = g_env;
	while (tmp)
	{
		ft_printf("%s\n", tmp->env);
		tmp = tmp->next;
	}
>>>>>>> 402b7099ea754a2d9a234393308d1721431d8bf7
	return (0);
}

void	get_envs(char **envp)
{
	int			i;
<<<<<<< HEAD
	i = 0;
	while (envp[i])
		i++;
	g_env = (char **)calloc(sizeof(char *) * i + 1, 1);
	i = 0;
	while (envp[i])
	{
		g_env[i] = (char *)malloc(ft_strlen(envp[i]) + 1);
		ft_strcpy(g_env[i], envp[i]);
		i++;
	}
=======
	t_env		*tmp;

	i = 0;
	while (envp[i])
	{
		if (!g_env)
		{
			g_env = (t_env *)ft_calloc(sizeof(t_env), 1);
			g_env->env = ft_strdup(envp[i]);
			tmp = g_env;
		}
		else
		{
			tmp->next = (t_env *)ft_calloc(sizeof(t_env), 1);
			tmp = tmp->next;
			tmp->env = ft_strdup(envp[i]);
		}
		i++;
	}
	t_env *qwe = g_env;
	while (qwe)
	{
		ft_printf("%s\n", qwe->env);
		qwe = qwe->next;
	}
>>>>>>> 402b7099ea754a2d9a234393308d1721431d8bf7
}