#include <unistd.h>
#include "libftprintf.h"

int	ft_pwd(char **args)
{
	char		homepath[1024];

	getcwd(homepath, 1024);
	ft_printf("%s\n", homepath);
	// exit(0);
}