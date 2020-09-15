/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:14 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/16 02:07:22 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <bits/waitstatus.h>
#include "minishell.h"
#include "libftprintf.h"
#include "libft.h"
#include "parser.h"
#include "redirect.h"

int		child_process(char **args)
{
	g_fork_flag = 1;
	if (g_pipe_next == 2)
	{
		dup2(g_pipe[1], 1);
		close(g_pipe[0]);
	}
	change_underscores(args[0], args);
	args[0] = add_path(args[0]);
	if (execve(args[0], args, g_env_vars) == -1)
	{
		free_args(&args);
		exit(print_error("Command not found", 127));
	}
	exit(0);
}

int		start_fork(char **args)
{
	int			status;
	pid_t		pid;

	pid = fork();
	if (pid == 0)
		g_exit_status = child_process(args);
	else if (pid > 0)
	{
		if (g_pipe_next == 2)
		{
			dup2(g_pipe[0], 0);
			close(g_pipe[1]);
		}
		wait(&status);
		g_exit_status = WEXITSTATUS(status);
	}
	else
		g_exit_status = print_error(strerror(errno), 1);
	g_pipe_prev = g_pipe_next;
	g_pipe_next = 0;
	g_fork_flag = 0;
	return (0);
}

int		self_funcs(char **args, int i)
{
	int	(*funcs[8])(char **) = {NULL,
									ft_echo,
									ft_cd,
									ft_pwd,
									ft_export,
									ft_unset,
									ft_env,
									ft_exit};

	if (g_pipe_next == 2)
	{
		dup2(g_pipe[0], 0);
		dup2(g_pipe[1], 1);
	}
	return (funcs[i](&args[1]));
}

void	minishell(t_list *parse)
{
	int			i;
	int			error;
	char		**args;

	i = 0;
	error = 0;
	while (parse)
	{
		args = get_args_str(parse);
		change_underscores(args[0], args);
		error = check_redirect(&parse);
		if (!error && g_pipe_next != 2 && (i = is_func(args[0])))
			g_exit_status = self_funcs(args, i);
		else if (!error)
			start_fork(args);
		while (parse && !is_redirect(get_str(parse)))
			parse = parse->next;
		if (parse)
			parse = parse->next;
		free_args(&args);
		open_stdin_stdout();
	}
}

//TODO clean function
int		loop_read(void)
{
	t_buf		buf;
	char		*input;
	t_list		*parse;

	parse = NULL;
	init_buf(&buf);
	while (1)
	{
		input = NULL;
		if (show_prompt())
			return (1);
		if ((read_stdin(&buf, &input)) && buf.buf[0] != 10)
		{
			if (flush_buf(&buf, &input))
				return (1);
			parse = parser(input);
			minishell(parse);
			free(input);
			ft_lstclear(&parse, free);
		}
		else
			ctrl_d();
	}
}

int		main(int argc, char **argv, char **envp)
{
	if (argc > 1 || argv[1])
		return (ft_putendl_fd("Error. Invalid arguments\n", 2));
	if (get_envs(envp, &g_env_vars))
		print_error(strerror(errno), 1);
	save_stdin_stdout();
	signal_handler();
	if (!loop_read())
		ft_putendl_fd("Error\n", 2);
	ctrl_d();
}
