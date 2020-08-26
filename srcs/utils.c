#include "libft.h"
#include "minishell.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int		ft_strlenbuf(char **buf)
{
	int	i;

	i = 0;
	while (buf[i])
		i++;
	return (i);
}

char 	**get_args_str(char **parse, int i)					// получаем массив строк - аргументы функции
{
	int		j;
	char	**args;

	j = i;
	while ((parse[j] && !check_operator(parse[j])))
		j++;
	args = (char **)malloc(sizeof(char *) * (j + 1));
	j = 0;
	while ((parse[i] && !check_operator(parse[i])))
		args[j++] = ft_strdup(parse[i++]);
	args[j] = NULL;
	return (args);
}
