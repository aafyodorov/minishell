#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libftprintf.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"

// void	check_redirect(t_list *parse)
// {
// 	while (parse && !is_redirect(get_str(parse)))
// 		parse = parse->next;
// 	if (!parse)
// 		return ;
// 	else if (!ft_strcmp(get_str(parse), ">"))
// 		close_stdin_stdout(get_str(parse->next));	
// }

void	child_process(t_list *parse)
{
	int			j;
	char		**args;
	const int	(*funcs[7])(char **) = {ft_echo,
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
		{
			ft_printf("%s\n", strerror(errno));
			exit(1);
		}
	}
	if (g_fd[4])
		open_stdin_stdout();
	//exit(0);
}

void	minishell(t_list *parse)
{
	int			j;
	pid_t		pid;

	ft_bzero(&g_fd, sizeof(int) * 5);
	while (parse)
	{
		// pipe(g_pipe);
		if (!ft_strcmp(get_str(parse), "cd"))
		{
			chdir("/bin");
		parse = parse->next;
		}
		pid = fork();
		if (pid == 0)
		{
			child_process(parse);
			zzz = 1;
		}
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
