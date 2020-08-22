#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "libftprintf.h"
#include "libft.h"

int			ft_echo(char *str) {
	ft_printf("%s\n", str);
	return (0);
}

int			ft_cd(char *str) {
	int		i;
	char	tmp[1024];

	i = 0;
	if (!str)
	{
		while (ft_strncmp("HOME=", g_env[i], 5))
			i++;
		ft_strcpy(tmp, &g_env[i][5]);
		chdir(tmp);
		return (0);
	}
	chdir(str);
	return (0);
}

int			ft_pwd(char *str) {
	ft_printf("pwd\n");
	return (0);
}

int			ft_export(char *str) {
	ft_printf("export\n");
	return (0);
}

int			ft_unset(char *str) {
	ft_printf("unset\n");
	return (0);
}

int			ft_env(char *str) {
	int		i;

	i = 0;
	if (str)
		return (ft_printf("Invalid argument\n"));
	while (g_env[i])
		ft_printf("%s\n", g_env[i++]);
	return (0);
}

int			ft_exit(char *str) {
	ft_printf("exit\n");
	return (0);
}

char*		start_fork(char *str, char *arg)
{
	int		i;
	pid_t	pid;
	int			(*funcs[7])(char *) = {ft_echo,
										ft_cd,
										ft_pwd,
										ft_export,
										ft_unset,
										ft_env,
										ft_exit};
	const char	*funcs_str[7] = {"echo",
								"cd",
								"pwd",
								"export",
								"unset",
								"env",
								"exit"};

	i = -1;
	pid = fork();
	if (pid > 0)	
		wait(0);
	else if (pid == 0)
	{
		while (++i < 7)
		{
			if (ft_strcmp(funcs_str[i], str))
			{
				funcs[i](arg);
				exit(0);
			}
		}
	}
	else
	{
		ft_printf("%s\n", strerror(errno));
		return (NULL);
	}
	return (NULL);
}

void	minishell(char **args) {
	char	*res;
	int		i;
	int		j;

	i = 0;
	res = NULL;
	while (args[i])
	{
		if (check_func(args[i]) && (!args[i + 1] || !check_args(args[i + 1])))
			res = start_fork(args[i], NULL);
		else if (check_func(args[i]) && res)
			res = start_fork(args[i], res);
		else if (check_func(args[i]) && args[i + 1] && check_args(args[i + 1]))
			res = start_fork(args[i], args[i + 1]);
		else
			ft_printf("%s\n", "command not found");
		i += res ? 2 : 1;
		if (check_operator(args[i]))
		{
			ft_printf("s\n", res);
			res = NULL;
			i++;
		}
	}
}

// void	check_args(char **args)
// {
// 	pid_t		pid;
// 	const char	*funcs[7] = {"echo",
// 							"cd",
// 							"pwd",
// 							"export",
// 							"unset",
// 							"env",
// 							"exit"};
// 	pid = fork();
// 	if (pid == 0)
// 		wait();
// 	while (*args)
// 	{
// 		if (!ft_strcmp());
// 	}

// }

void	get_envs(char **envp)
{
	int			i;

	i = 0;
	while (envp[i])
		i++;
	g_env = (char **)calloc(sizeof(char *) * i + 1, 1);
	i = 0;
	while (envp[i])
	{
		g_env[i] = (char *)malloc(ft_strlen(envp[i]) + 1);
		ft_strcpy(g_env[i], envp[i]);
		i++;
	}
}

int		main(int argc, char **argv, char **envp)
{
	char		*str_args;
	char		**args;
	char		homepath[1024];

	get_envs(envp);																// записываем список переменных среды, прищедших через envp в глобальную переменную 
	memset(homepath, 0, 1024);
	getcwd(homepath, 1024);														// записываем в homepath путь текущей директории
	ft_printf("%sminishell%s:%s~%s%s$ ", GREEN, RESET, BLUE, homepath, RESET);
	str_args = NULL;
	args = NULL;
	g_env = NULL;
	while ((get_next_line(1, &str_args) != -1))									// бесконечный цикл для ввода команд
	{
		if(!(args = ft_split(str_args, ' ')))
			return (free_args(&g_env) +
					free_str(&str_args) +
					ft_printf("%s\n", strerror(errno)));
		getcwd(homepath, 1024);
		minishell(args);
		ft_printf("%sminishell%s:%s~%s%s$ ", GREEN, RESET, BLUE, homepath, RESET);
		free_str(&str_args);
		free_args(&args);
		str_args = NULL;
	}
	free_str(&str_args);
	free_args(&args);
	free_args(&g_env);
}
