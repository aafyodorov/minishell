/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:14 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/01 15:30:55 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "libftprintf.h"
#include "libft.h"
#include "parser.h"

void	check_redirect(t_list *parse)
{
	while (parse && !is_redirect(get_str(parse)))
		parse = parse->next;
	if (!parse)
		return ;
	else if (!ft_strcmp(get_str(parse), ">"))
		close_stdin_stdout(get_str(parse->next->content));	
}

void	child_process(t_list *parse, int i)
{
	int		j;
	char	**args;
	int		(*funcs[7])(char **) = {ft_echo,
									ft_cd,
									ft_pwd,
									ft_export,
									ft_unset,
									ft_env,
									ft_exit};

	args = get_args_str(parse);
	change_underscores(args[0], args);
	check_redirect(parse);
	if ((j = is_func(args[0])) >= 0)
		funcs[j](&args[1]);
	else
	{
		args[0] = add_path(args[0]);
		if (execve(args[0], args, g_env_vars) == -1)
			ft_printf("%s\n", strerror(errno));
	}
	if (g_fd[4])
		open_stdin_stdout();
}

void	minishell(t_list *parse)
{
	int		i;
	int		j;
	pid_t	pid;

	i = 0;
	ft_bzero(&g_fd, sizeof(int) * 5);
	while (parse)
	{
		// pipe(g_pipe);
		pid = fork();
		if (pid == 0)
			child_process(parse, i);
		else if (pid > 0)	
			wait(0);
		else
		{
			ft_printf("%s\n", strerror(errno));
			g_exit_status = errno;
		}
		while (parse && !is_redirect(get_str(parse)))
			parse = parse->next;
		if (parse)
			parse = parse->next;
	}
}

int		main(int argc, char **argv, char **envp)
{
	char		*input;
	t_list		*parse;
	char		homepath[1024];

	get_envs(envp, &g_env_vars);
	memset(homepath, 0, 1024);
	getcwd(homepath, 1024);														// записываем в homepath путь текущей директории
	ft_printf("%sminishell%s:%s~%s%s$ ", GREEN, RESET, BLUE, homepath, RESET);
	input = NULL;
	signal_handler();
	while ((get_next_line(0, &input) != -1))									// бесконечный цикл для ввода команд
	{
		parse = parser(input);
		minishell(parse);
		getcwd(homepath, 1024);
		ft_printf("%sminishell%s:%s~%s%s$ ", GREEN, RESET, BLUE, homepath, RESET);
		free_str(&input);
		ft_lstclear(&parse, free);
		input = NULL;
	}
	free_str(&input);
	ft_lstclear(&parse, free);
	free_args(&g_env_vars);
}
