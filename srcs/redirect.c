#include "libft.h"
#include "minishell.h"
#include "redirect.h"

int		redirect_1(t_list *parse)
{
	return (0);
}

int		redirect_2(t_list *parse)
{
	int error;

	// g_fd[0] = dup(0);
	// g_fd[1] = dup(1);
	// close(0);
	// close(1);
	if (pipe(g_pipe) == -1)
	// if (g_fd[0] == -1 || g_fd[1] == -1 || error == -1)
	{
		g_exit_status = errno;
		return (1);
	}
	g_exit_status = 0;
	return (0);
}

static char	*get_filename(t_list *parse)
{
	char		*res;

	res = NULL;
 	while (parse && !(is_redirect(get_str(parse))))
		parse = parse->next;
	if (parse->next)
		res = get_str(parse->next);
	return (res);
}

int		redirect_3(t_list *parse)
{
	const char	*filename = get_filename(parse);

	if (!filename)
	{
		g_exit_status = 2;
		ft_printf("echo: syntax error");
		return (2);
	}
	g_fd[1] = dup(1);
	close(1);
	g_pipe[1] = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (g_pipe[1] < 0)
	{
		g_exit_status = 2;
		ft_printf("echo: syntax error");				////// написать функцию вывода ошибки
		return (2);
	}
	return (0);
}

int		redirect_4(t_list *parse)
{
	const char	*filename = get_filename(parse);

	if (!filename)
	{
		g_exit_status = 2;
		ft_printf("echo: syntax error");
		return (2);
	}
	g_fd[1] = dup(1);
	close(1);
	g_pipe[1] = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (g_pipe[1] < 0)
	{
		g_exit_status = 2;
		ft_printf("echo: syntax error");				////// написать функцию вывода ошибки
		return (2);
	}
	return (0);
}

int		redirect_5(t_list *parse)
{
		const char	*filename = get_filename(parse);

	if (!filename)
	{
		g_exit_status = 2;
		ft_printf("echo: syntax error");
		return (2);
	}
	g_fd[0] = dup(0);
	close(0);
	g_pipe[0] = open(filename, O_RDONLY);
	if (g_pipe[0] < 0)
	{
		g_exit_status = errno;
		perror("cat");
		return (1);
	}
	return (0);
}