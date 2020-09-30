/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 03:30:06 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/26 20:26:31 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		self_funcs(char **args, int i)
{
	if (g_pipe_next == 2)
	{
		dup2(g_pipe[0], 0);
		dup2(g_pipe[1], 1);
	}
	return (g_funcs[i](&args[1]));
}

int		child_process(char **args, t_list **list)
{
	char		func_name[1024];
	int			i;

	i = 0;
	g_fork_flag = 1;
	open_pipe_child();
	ft_strcpy(func_name, args[0]);
	change_underscores(args[0], args);
	if (args && (i = is_func(args[0])))
		g_exit_status = self_funcs(args, i);
	else
	{
		args[0] = add_path(args[0]);
		if (execve(args[0], args, g_env_vars) == -1)
		{
			ft_lstclear(list, free);
			free_args(&args);
			free_args(&g_env_vars);
			ft_lstclear(&g_loc_vars, del_var_cont);
			ft_printf("%s: ", func_name);
			exit(print_error("command not found", 127));
		}
	}
	exit(0);
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
		open_pipe_parent();
		wait(&status);
		g_exit_status = WEXITSTATUS(status);
		if ((WIFSIGNALED(status)))
		{
			if (status == 131)
				ft_printf("quit (core dumped) %s\n", args[0]);
			g_exit_status = (status != 131) ? 130 : status;
		}
	}
	else
		g_exit_status = print_error(strerror(errno), 1);
	g_pipe_prev = g_pipe_next;
	g_pipe_next = 0;
	g_fork_flag = 0;
	return (0);
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
		if (args && !error && g_pipe_next != 2 && (i = is_func(args[0])))
			g_exit_status = self_funcs(args, i);
		else if (args && !error)
			start_fork(args, &list);
		if (g_exit_status == 130)
			break ;
		while (parse && !is_redirect(get_str(parse), get_flag_parser(parse)))
			parse = parse->next;
		parse = parse ? parse->next : NULL;
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
		if (read_stdin(&buf, &input) && buf.buf[0] != 10)
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
