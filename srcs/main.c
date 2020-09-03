/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:14 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/03 00:41:11 by fgavin           ###   ########.fr       */
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

//TODO change while to while(1)
//TODO handle ~
int		loop_read(char *input, t_list **parse)
{
	int 		read_b;
	t_buf		buf;

	init_buf(&buf);
	while (read_b == read_b + 1 - 1)									// бесконечный цикл для ввода команд
	{
		if (show_prompt())
			return (1);
		if ((read_b = read_stdin(&buf, &input)))
		{
			if(flush_buf(&buf, &input))
				return (1);
			*parse = parser(input);
			minishell(*parse);
			//show_prompt();										<- Old pos
			free_str(&input);
			ft_lstclear(parse, free);
			input = NULL;
		}
		else if (!read_b)
			ctrl_d();
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	char		*input;
	t_list		*parse;

	argc = 0;
	*argv = NULL;
	input = NULL;
	get_envs(envp, &g_env_vars);
	signal_handler();
	//show_prompt();												<- Old pos
	loop_read(input, &parse);
	free_str(&input);
}
