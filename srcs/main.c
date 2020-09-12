/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:14 by pdemocri          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/09/12 22:03:44 by pdemocri         ###   ########.fr       */
=======
/*   Updated: 2020/09/09 01:26:05 by fgavin           ###   ########.fr       */
>>>>>>> 41af8fc1cc432629be1c3ff6fb5f00e3112c0343
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

void	child_process(char **args)
{
	pid_t		child;

	g_fork_flag = 1;
	if (g_pipe_next == 2)
	{
		dup2(g_pipe[1], 1);
		close(g_pipe[0]);
	}
	change_underscores(args[0], args);
	args[0] = add_path(args[0]);
	if (execve(args[0], args, g_env_vars) == -1)
<<<<<<< HEAD
		exit(print_error("Command not found", 127));
	exit(0);
}

int		start_fork(char **args, t_list *parse)
{
	int			status;
	pid_t		pid;
=======
	{
		ft_printf("%s\n", strerror(errno));
		g_exit_status = errno;
		g_fork_flag = 0;
		exit(1);
	}
	// if (g_fd[4])
	// 	open_stdin_stdout();
	//exit(0);
}

int		start_fork(char **args)
{
	pid_t	pid;
>>>>>>> 41af8fc1cc432629be1c3ff6fb5f00e3112c0343

	pid = fork();
	if (pid == 0)
		child_process(args);
	else if (pid > 0)
	{
<<<<<<< HEAD
		if (g_pipe_next == 2)
		{
			dup2(g_pipe[0], 0);
			close(g_pipe[1]);
		}
		wait(&status);
		g_exit_status = WEXITSTATUS(status);
=======
		ft_printf("%s\n", strerror(errno));
		g_exit_status = errno;
		return (errno);
>>>>>>> 41af8fc1cc432629be1c3ff6fb5f00e3112c0343
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
	const int	(*funcs[8])(char **) = {NULL,
									ft_echo,
									ft_cd,
									ft_pwd,
									ft_export,
									ft_unset,
									ft_env,
									ft_exit};

<<<<<<< HEAD
	if (g_pipe_next == 2)
	{
		dup2(g_pipe[0], 0);
		dup2(g_pipe[1], 1);
	}
	funcs[i](&args[1]);
}

void	minishell(t_list *parse)
{
	int			i;
	int			error;
	char		**args;

	i = 0;
	error = 0;
	save_stdin_stdout();
=======
	//i = 0;
>>>>>>> 41af8fc1cc432629be1c3ff6fb5f00e3112c0343
	while (parse)
	{
		args = get_args_str(parse);
		change_underscores(args[0], args);
		error = check_redirect(&parse);
		if (!error && g_pipe_next != 2 && (i = is_func(args[0])))
			g_exit_status = self_funcs(args, i);
		else if (!error)
			start_fork(args, parse);
		while (parse && !is_redirect(get_str(parse)))
			parse = parse->next;
		if (parse)
			parse = parse->next;
<<<<<<< HEAD
		open_stdin_stdout();
=======
		free_args(&args);
>>>>>>> 41af8fc1cc432629be1c3ff6fb5f00e3112c0343
	}
}

//TODO clean function
int		loop_read(void)
{
<<<<<<< HEAD
	int				read_b;
	t_buf			buf;
	char			*input;
	t_list			*parse;
=======
	//int 		read_b;
	t_buf		buf;
	char		*input;
	t_list		*parse;
>>>>>>> 41af8fc1cc432629be1c3ff6fb5f00e3112c0343

	parse = NULL;
	init_buf(&buf);
	while (1)
	{
		printf("%d\n", getpid());//del
		input = NULL;
		if (show_prompt())
			return (1);
		if ((/*read_b =*/ read_stdin(&buf, &input)) && buf.buf[0] != 10)
		//if (get_next_line(0, &input))
		{
			if (flush_buf(&buf, &input))
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
	if (get_envs(envp, &g_env_vars))
		print_error(strerror(errno), 1);
	signal_handler();
	if (!loop_read())
		ft_putendl_fd("Error.\n", 2);
	ctrl_d();
}
