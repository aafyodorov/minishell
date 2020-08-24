/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:14 by pdemocri          #+#    #+#             */
/*   Updated: 2020/08/25 01:43:47 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "libftprintf.h"
#include "libft.h"

int			ft_echo(char **args, char **env, char *ret)
{
	int			i;

	i = 0;
	if (!ft_strcmp(args[0], "-n"))
		i++;
	while (args[i])
		ft_printf("%s", args[i++]);
	if (ft_strcmp(args[0], "-n"))
		ft_printf("\n");
	return (0);
}

int			ft_cd(char **args, char **env, char *ret)
{
	int			i;
	char		tmp[1024];

	i = 0;
	while (args[i])
		i++;
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

int			ft_pwd(char **args, char **env, char *ret)
{
	char		homepath[1024];

	getcwd(homepath, 1024);
	ft_printf("%s\n", homepath);
	return (0);
}

int			ft_export(char **args, char **env, char *ret)
{
	ft_printf("export\n");
	return (0);
}

int			ft_unset(char **args, char **env, char *ret)
{
	ft_printf("unset\n");
	return (0);
}

int			ft_exit(char **args, char **env, char *ret)
{
	ft_printf("exit\n");
	return (0);
}

char*		start_fork(char *func, char **args, char *ret)
{
	int			i;
	pid_t		pid;
	int			(*funcs[7])(char **, char **, char *) = {ft_echo,
														ft_cd,
														ft_pwd,
														ft_export,
														ft_unset,
														ft_env,
														ft_exit};

	pid = fork();
	if (pid == 0)
	{
		if ((i = check_func(func)) >= 0)
			funcs[i](args, g_env, ret);
		else
			execve(func, args, g_env);
	}
	else if (pid > 0)	
		wait(0);
	else
	{
		ft_printf("%s\n", strerror(errno));
		return (NULL);
	}
	return (NULL);
}

char 	**get_args_str(char **parse, int i)					// получаем массив строк - аргументы функции
{
	int		j;
	char	**args;

	j = i + 1;
	while ((parse[j] && !check_operator(parse[j])))
		j++;
	args = (char **)malloc(sizeof(char *) * j);
	j = 0;
	i++;
	while ((parse[i] && !check_operator(parse[i])))
		args[j++] = ft_strdup(parse[i++]);
	args[j] = NULL;
	return (args);
}

void	minishell(char **parse) {
	int		i;
	char	**args;
	char	*ret;

	i = 0;
	ret = NULL;
	while (parse[i])
	{
		if (!check_operator(parse[i]))
		{
			args = get_args_str(parse, i);
			ret = start_fork(parse[i], args, ret);
			while (parse[i] && !check_operator(parse[i]))
				i++;
			free_args(&args);
		}
		else if (check_operator(parse[i]))
			return;									///////////////////////////добавить_функцию//////////////////////////////
	}
}

int		main(int argc, char **argv, char **envp)
{
	char		*input;
	char		**parse;
	char		homepath[1024];

	get_envs(envp);																// записываем список переменных среды, прищедших через envp в глобальную переменную 
	// g_env = envp;
	memset(homepath, 0, 1024);
	getcwd(homepath, 1024);														// записываем в homepath путь текущей директории
	ft_printf("%sminishell%s:%s~%s%s$ ", GREEN, RESET, BLUE, homepath, RESET);
	input = NULL;
	parse = NULL;
	while ((get_next_line(0, &input) != -1))									// бесконечный цикл для ввода команд
	{
		if(!(parse = ft_split(input, ' ')))
			return (free_args(&g_env) +
					free_str(&input) +
					ft_printf("%s\n", strerror(errno)));
		minishell(parse);
		getcwd(homepath, 1024);
		ft_printf("%sminishell%s:%s~%s%s$ ", GREEN, RESET, BLUE, homepath, RESET);
		free_str(&input);
		free_args(&parse);
		input = NULL;
	}
	free_str(&input);
	free_args(&parse);
	free_args(&g_env);
}
