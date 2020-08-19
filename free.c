#include <stdlib.h>

int	free_str(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (0);
}

int	free_args(char ***args)
{
	int	i;

	i = 0;
	while (*args && (*args)[i])
		free((*args)[i++]);
	free(*args);
	*args = NULL;
	return (0);
}