#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "parser.h"

int				ft_strlenbuf(char **buf)
{
	int			i;

	i = 0;
	while (buf[i])
		i++;
	return (i);
}

static char*	ft_strdup_arg(char *str, unsigned flag, char **env)
{
	int			i;
	const int	len = ft_strlen(str);
	char		*arg;

	i = 0;
	if (!ft_strcmp(str, "?") && flag == 2)
		arg = ft_itoa(g_exit_status);
	else if (flag == 0)
		arg = strdup(str);
	else if (flag == 2)
	{
		while (env[i])
		{
			if (!ft_strncmp(str, env[i], len) && env[i][len] == '=')
				return (arg = ft_strdup(&env[i][len + 1]));
			i++;
		}	
	}
	return (arg);
}

char 			**get_args_str(t_list *parse, char **env)					// получаем массив строк - аргументы функции
{
	int		i;
	int		len;
	char	**args;
	t_list	*tmp;

	len = 0;
	tmp = parse;
	while ((tmp && !is_redirect(get_str(tmp))))
	{
		len++;
		tmp = tmp->next;
	}
	args = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while ((parse && i < len))
	{
		args[i++] = ft_strdup_arg(get_str(parse),
									get_flag_parser(parse), env);
		parse = parse->next;
	}
	args[i] = NULL;
	return (args);
}
