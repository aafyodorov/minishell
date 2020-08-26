#include "libft.h"
#include "libftprintf.h"
#include "minishell.h"

static char	*substitution(char *buf, char *args, char **env)
{
	int		i;
	char	tmp[1024];
	int		len;

	i = 0;
	ft_strcpy(tmp, &args[1]);
	len = ft_strlen(tmp);
	while (env[i])
	{
		if (!ft_strncmp(tmp, env[i], len) && env[i][len] == '=')
			buf = ft_strcpy(buf, &env[i][len + 1]);
		i++;
	}
	return (buf);
}

int			ft_echo(char **args, char **env, char *ret)
{
	int		i;
	int		j;
	char	subst[4048];

	i = 0;
	ft_bzero(subst, 4048);
	if (!ft_strcmp(args[0], "-n"))
		i++;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "$?"))
			ft_printf("%i", g_exit_status);
		else if (args[i][0] == '$')
			ft_printf("%s", substitution(subst, args[i], env));
		else
			ft_printf("%s", args[i]);
		i++;
	}
	if (ft_strcmp(args[0], "-n"))
		ft_printf("\n");
	return (0);
}