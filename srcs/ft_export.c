#include "libft.h"
#include "parser.h"

static char	*find_env_var(char **var_list, char *str)
{
	int		i;

	i = 0;
	while (var_list[i])
	{
		if (!ft_strncmp(var_list[i], str, ft_strlen(str)) &&
			var_list[i][ft_strlen(str)] == '=')
			return (var_list[i]);
		i++;
	}
	return (NULL);
}

static char	*find_loc_var(t_list *var_list, char *str)
{
	char	*content;

	while (var_list)
	{
		content = var_list->content;
		if (!ft_strncmp(content, str, ft_strlen(str)) &&
			content[ft_strlen(str)] == '=')
			return (var_list->content);
		var_list = var_list->next;
	}
	return (NULL);
}

int				ft_export(char **args)
{
	int		i;
	char	*exp;
	char	*tmp;

	exp = NULL;
	i = -1;
	while (args[++i])
	{
		exp = find_env_var(g_env_vars, args[i]);
		if (exp)
			continue;
		tmp = find_loc_var(g_loc_vars, args[i]);
		if (tmp)
			g_env_vars[ft_strlenbuf(g_env_vars)] = ft_strdup(tmp);
	}
	return (0);
}