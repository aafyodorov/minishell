/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:14 by pdemocri          #+#    #+#             */
/*   Updated: 2020/08/26 07:02:35 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "libftprintf.h"
#include "libft.h"

char*		start_fork(char *func, char **args, char *ret, char **env)
{
	int			i;
	pid_t		pid;
	char		**null;
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
		change_underscores(func, args, env);
		if ((i = check_func(func)) >= 0)
			funcs[i](args, env, ret);
		else
		{
			null = (char **)ft_calloc(sizeof(char *), 2);
			null[0] = " ";
			func = add_path(func, env);
			execve(func, (args = args[0] ? args : null), env);
		}
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

void	minishell(char **parse, char **env)
{
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
			ret = start_fork(parse[i], args, ret, env);
			while (parse[i] && !check_operator(parse[i]))
				i++;
			free_args(&args);
		}
		else if (check_operator(parse[i]))
			i++;									///////////////////////////добавить_функцию//////////////////////////////
	}
}

int		main(int argc, char **argv, char **envp)
{
	char		*input;
	char		**parse;
	char		**env;
	char		homepath[1024];

	env = get_envs(envp);
	memset(homepath, 0, 1024);
	getcwd(homepath, 1024);														// записываем в homepath путь текущей директории
	ft_printf("%sminishell%s:%s~%s%s$ ", GREEN, RESET, BLUE, homepath, RESET);
	input = NULL;
	parse = NULL;
	while ((get_next_line(0, &input) != -1))									// бесконечный цикл для ввода команд
	{
		if(!(parse = ft_split(input, ' ')))
			return (free_args(&env) +
					free_str(&input) +
					ft_printf("%s\n", strerror(errno)));
		minishell(parse, env);
		getcwd(homepath, 1024);
		ft_printf("%sminishell%s:%s~%s%s$ ", GREEN, RESET, BLUE, homepath, RESET);
		free_str(&input);
		free_args(&parse);
		input = NULL;
	}
	free_str(&input);
	free_args(&parse);
	free_args(&env);
}
