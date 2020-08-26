#include "libftprintf.h"
#include "minishell.h"

static void	delete_var(char ***env, int j)
{
	char	*tmp;

	if (j == ft_strlenbuf(*env) - 1)
	{
		free((*env)[j]);
		(*env)[j] = NULL;
	}
	else
	{
		tmp = (*env)[j];
		while ((*env)[j])
		{
			(*env)[j] = (*env)[j + 1];
			j++;
		}
		free((*env)[j]);
	}
}

void		change_underscores(char *func, char **args, char **env)
{
	int		i;
	char	*tmp;

	tmp = args[0] ? args[ft_strlenbuf(args) - 1] : func;
	i = 0;
	while (ft_strncmp(env[i], "_=", 2))
		i++;
	free(env[i]);
	env[i] = ft_strjoin("_=", tmp);
}

int			ft_unset(char **args, char **env, char *ret)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	if (!ft_strncmp(args[i], "_", 1))
	{
		change_underscores("env", args, env);
		return (0);
	}
	while (args[i])
	{
		j = 0;
		len = ft_strlen(args[i]);
		while (env[j])
		{
			if (!ft_strncmp(args[i], env[j], len))
				delete_var(&env, j);
			j++;
		}
		i++;
	}
	return (0);
}