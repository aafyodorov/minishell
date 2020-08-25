#include "libftprintf.h"
#include "minishell.h"

int	ft_unset(char **args, char **env, char *ret)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		j = 0;
		len = ft_strlen(args[i]);
		while (env[j])
		{
			if (!ft_strncmp(args[i], env[j], len))
			{
				if (j == ft_strlenbuf(env) - 1)
				{
					free(env[j]);
					env[j] = NULL;
				}
				else
				{
					free(env[j]);
					env[j] = env[ft_strlenbuf(env) - 1];
					env[ft_strlenbuf(env) - 1] = NULL;
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}