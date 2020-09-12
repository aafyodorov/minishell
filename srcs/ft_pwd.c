#include <unistd.h>
#include "minishell.h"
#include "libftprintf.h"

int	ft_pwd(char **args)
{
	char		homepath[1024];

	if (!getcwd(homepath, 1024))
		return (print_error(strerror(errno),1));
	ft_printf("%s\n", homepath);
	return (0);
}