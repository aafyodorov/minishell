#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "libftprintf.h"
#include "minishell.h"

int	ft_cd(char **args, char **env, char *ret)
{
	int			i;
	char		tmp[1024];

	i = ft_strlenbuf(args);
	if (i > 1)
		return (ft_printf("cd: слишком много аргументов\n"));
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