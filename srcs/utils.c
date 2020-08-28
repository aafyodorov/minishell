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
	int		len;
	char	**args;

	j = i;
	len = 0;
	while ((parse[j] && !is_redirect(parse[j])))
	{
		len++;
		j++;
	}
	args = (char **)malloc(sizeof(char *) * (len + 1));
	j = 0;
	while ((parse[i] && j < len))
		args[j++] = ft_strdup(parse[i++]);
	args[j] = NULL;
	return (args);
}
