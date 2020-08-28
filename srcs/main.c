/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:14 by pdemocri          #+#    #+#             */
/*   Updated: 2020/08/27 18:41:57 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "libftprintf.h"
#include "libft.h"

void	check_redirect(char **parse, int i)
{
	while (parse[i] && !is_redirect(parse[i]))
		i++;
	if (!parse[i])
		return ;
	else if (!ft_strcmp(parse[i], ">"))
		close_stdin_stdout(parse[i + 1]);	
}

void	child_process(char **parse, char **env, int i)
{
	int		j;
	char	**args;
	int		(*funcs[7])(char **, char **) = {ft_echo,
											ft_cd,
											ft_pwd,
											ft_export,
											ft_unset,
											ft_env,
											ft_exit};

	args = get_args_str(parse, i);
	change_underscores(args[0], args, env);
	check_redirect(parse, i);
	if ((j = is_func(args[0])) >= 0)
		funcs[j](&args[1], env);
	else
	{
		args[0] = add_path(args[0], env);
		if (execve(args[0], args, env) == -1)
			ft_printf("%s\n", strerror(errno));
	}
	if (g_fd[4])
		open_stdin_stdout();
}

void	minishell(char **parse, char **env)
{
	int		i;
	int		j;
	pid_t	pid;

	i = 0;
	ft_bzero(&g_fd, sizeof(int) * 5);
	while (parse[i])
	{
		// pipe(g_pipe);
		pid = fork();
		if (pid == 0)
			child_process(parse, env, i);
		else if (pid > 0)	
			wait(0);
		else
		{
			ft_printf("%s\n", strerror(errno));
			g_exit_status = errno;
		}
		while (parse[i] && !is_redirect(parse[i]))
			i++;
		i += parse[i] ? 1 : 0;
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
	signal_handler();
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
