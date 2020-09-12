/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:14 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/12 20:06:42 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <bits/waitstatus.h>
#include "minishell.h"
#include "libftprintf.h"
#include "libft.h"
#include "parser.h"
#include "redirect.h"

void	child_process(char **args)
{
	pid_t	child;

	g_fork_flag = 1;
	change_underscores(args[0], args);
	args[0] = add_path(args[0]);
	if (execve(args[0], args, g_env_vars) == -1)
	{
		ft_printf("%s\n", strerror(errno));
		g_exit_status = errno;
		g_fork_flag = 0;
		exit(1);
	}
}

int		start_fork(char **args, t_list *parse)
{	
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (g_pipe_next == 2)
		{
			dup2(g_pipe[1], 1);
			close(g_pipe[0]);
		}
		child_process(args);
	}
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
	{
		ft_printf("%s\n", strerror(errno));
		g_exit_status = errno;
	}
	g_pipe_prev = g_pipe_next;
	g_pipe_next = 0;
	g_fork_flag = 0;
}

int		self_funcs(char **args, int i)
{
	int		(*funcs[8])(char **) = {NULL,
									ft_echo,
									ft_cd,
									ft_pwd,
									ft_export,
									ft_unset,
									ft_env,
									ft_exit};

	funcs[i](&args[1]);
}

void	minishell(t_list *parse)
{
	int		i;
	int		error;
	char	**args;

	i = 0;
	error = 0;
	save_stdin_stdout();
	while (parse)
	{
		args = get_args_str(parse);
		change_underscores(args[0], args);
		// if (!g_pipe_next)
		error = check_redirect(&parse);
		if (!error && (i = is_func(args[0])))
			g_exit_status = self_funcs(args, i);
		else if (!error)
			start_fork(args, parse);
		while (parse && !is_redirect(get_str(parse)))
			parse = parse->next;
		if (parse)
			parse = parse->next;
		open_stdin_stdout();
	}
}

//TODO clean function
int		loop_read()
{
	int 		read_b;
	t_buf		buf;
	char		*input;
	t_list		*parse;

	int			a = 0;
	parse = NULL;
	init_buf(&buf);
	while (1)
	{
		printf("%d\n", getpid());//del
		input = NULL;
		if (show_prompt())
			return (1);
		if ((read_b = read_stdin(&buf, &input)) && buf.buf[0] != 10)
		//if (get_next_line(0, &input))
		{
			if(flush_buf(&buf, &input))
				return (1);
			parse = parser(input);
			minishell(parse);
			free(input);
			ft_lstclear(&parse, free);
		}
		else //if (!read_b && !buf.i)
			ctrl_d();
	}
}

int		main(int argc, char **argv, char **envp)
{

	*argv = NULL;
	argc = 0;
	get_envs(envp, &g_env_vars);
	signal_handler();
	if (!loop_read())
		ft_putendl_fd("Error.\n", 2);
	ctrl_d();
}
