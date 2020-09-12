#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "libftprintf.h"
#include "minishell.h"

static int	change_oldpwd(void)
{
	int			i;
	int			flag;
	char		buf[1024];

	i = 0;
	flag = 0;
	while (g_env_vars[i] && !flag)
	{
		if (!ft_strncmp(g_env_vars[i], "OLDPWD", 6))
		{
			free(g_env_vars[i]);
			g_env_vars[i] = ft_strjoin("OLDPWD=", getcwd(buf, 1024));
			return (g_env_vars[i] == NULL);
		}
		i++;
	}
	if (!flag)
		g_env_vars[ft_strlenbuf(g_env_vars)] = ft_strjoin("OLDPWD=", getcwd(buf, 1024));
	return (g_env_vars[i] == NULL);
}

int			ft_cd(char **args)
{
	int			i;
	char		tmp[1024];

	i = ft_strlenbuf(args);
	if (i > 1)
		return (print_error("cd: слишком много аргументов\n", 1));
	if (change_oldpwd())
		return (print_error(strerror(errno), 1));
	if (i == 0 || !ft_strcmp(args[0], "~"))
	{
		while (ft_strncmp("HOME=", g_env_vars[i], 5))
			i++;
		ft_strcpy(tmp, &g_env_vars[i][5]);
		chdir(tmp);
		return (!chdir(tmp) ? 0 : print_error(strerror(errno), 1));
	}
	return (!chdir(args[0]) ? 0 : print_error(strerror(errno), 1));
}