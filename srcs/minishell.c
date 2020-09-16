/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 03:30:06 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/16 06:44:55 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		child_process(char **args, t_list **list)
{
	int			ex_stat;

	ex_stat = 0;
	g_fork_flag = 1;
	if (g_pipe_next == 2)
	{
		dup2(g_pipe[1], 1);
		close(g_pipe[0]);
	}
	change_underscores(args[0], args);
	args[0] = add_path(args[0]);
	if (execve(args[0], args, g_env_vars) == -1)
		ex_stat = print_error("Command not found", 127);
	ft_lstclear(list, free);
	free_args(&args);
	ctrl_d();
	exit(ex_stat);
}

int		start_fork(char **args, t_list **list)
{
	int			status;
	pid_t		pid;

	pid = fork();
	if (pid == 0)
		g_exit_status = child_process(args, list);
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
	if (g_pipe_next == 2)
	{
		dup2(g_pipe[0], 0);
		dup2(g_pipe[1], 1);
	}
	return (g_funcs[i](&args[1]));
}

void	minishell(t_list *parse)
{
	int			i;
	int			error;
	char		**args;
	t_list		*list;

	list = parse;
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
			start_fork(args, &list);
		while (parse && !is_redirect(get_str(parse)))
			parse = parse->next;
		if (parse)
			parse = parse->next;
		free_args(&args);
		open_stdin_stdout();
	}
}

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
		if (!g_prompt && show_prompt())
			super_ctrl_d();
		if ((read_stdin(&buf, &input)) && buf.buf[0] != 10)
		{
			if (flush_buf(&buf, &input))
				return (1);
			parse = parser(input);
			free(input);
			g_prompt = 0;
			minishell(parse);
			ft_lstclear(&parse, free);
		}
		else
			super_ctrl_d();
	}
}
