/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:14 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/08 17:42:24 by pdemocri         ###   ########.fr       */
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
#include "redirect.h"

void	child_process(char **args)
{
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
	// if (g_fd[4]) 
	// 	open_stdin_stdout();
	//exit(0);
}

int		start_fork(char **args)
{	
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child_process(args);
	else if (pid > 0)
		wait(0);
	else
	{
		ft_printf("%s\n", strerror(errno));
		g_exit_status = errno;
	}
	g_fork_flag = 0;
}

void	minishell(t_list *parse)
{
	int		i;
	char	**args;
	int		(*funcs[8])(char **) = {NULL,
									ft_echo,
									ft_cd,
									ft_pwd,
									ft_export,
									ft_unset,
									ft_env,
									ft_exit};

	i = 0;
	while (parse)
	{
		args = get_args_str(parse);
		change_underscores(args[0], args);
		if ((i = is_func(args[0])))
			funcs[i](&args[1]);
		else
			start_fork(args);
		while (parse && !is_redirect(get_str(parse)))
			parse = parse->next;
		if (parse)
			parse = parse->next;
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
			open_fd(parse, &g_fd_head, &g_fd_list);
			minishell(parse);
			// close_fd(&g_fd_head);
			free(input);
			//free_str(&input);
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
