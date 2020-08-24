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
	return (0);
}

void	get_envs(char **envp)
{
	int			i;
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
}