#include "libft.h"

int	check_func(char *str)
{
	const char	*funcs_str[7] = {"echo",
								"cd",
								"pwd",
								"export",
								"unset",
								"env",
								"exit"};
	int			i;

	i = 0;
	while (i < 7)
		if (!ft_strcmp(funcs_str[i++], str))
			return (1);
	return (0);
}

int	check_args(char *str)
{
	return (0);
}

int	check_operator(char *str)
{
	return (0);
}
