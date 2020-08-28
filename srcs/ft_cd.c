#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "libftprintf.h"
#include "minishell.h"

static void	change_oldpwd(char **env)
{
	int			i;
	int			flag;
	char		buf[1024];

	i = 0;
	flag = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD", 6))
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", getcwd(buf, 1024));
			flag = 1;
		}
		i++;
	}
	if (!flag)
		env[ft_strlenbuf(env)] = ft_strjoin("OLDPWD=", getcwd(buf, 1024));
}

int			ft_cd(char **args, char **env)
{
	int			i;
	char		tmp[1024];

	i = ft_strlenbuf(args);
	if (i > 1)
		return (ft_printf("cd: слишком много аргументов\n"));
	change_oldpwd(env);
	if (i == 0)
	{
		while (ft_strncmp("HOME=", env[i], 5))
			i++;
		ft_strcpy(tmp, &env[i][5]);
		chdir(tmp);
		return (0);
	}
	if (chdir(args[0]))
		return (ft_printf("%s\n", strerror(errno)));
	return (0);
}