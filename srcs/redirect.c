#include "libft.h"
#include "minishell.h"
#include "redirect.h"

int		check_next_redirect(t_list *parse)
{
	int		i;

	i = 0;
	while (parse && !(i = is_redirect(get_str(parse))))
		parse = parse->next;
	return (i);
}

void	check_redirect(t_list **parse)
{
	const void		(*funcs[6])(char *) = {NULL,
										redirect_1,
										redirect_2,
										redirect_3
													};
										// redirect_4,
										// redirect_5};
	t_list			*tmp;

	g_pipe_status[1] = check_next_redirect(*parse);
	if (g_pipe_status[1] >= 3)
	{
		while (*parse && !is_redirect(get_str(*parse)))
			*parse = (*parse)->next;
		*parse = (*parse)->next;
	}
	if (g_pipe_status[1])
		funcs[g_pipe_status[1]](NULL);
}

void	redirect_1(char *func)
{
	return ;
}

void	redirect_2(char *func)
{
	g_fd[0] = dup(0);
	g_fd[1] = dup(1);
	close(0);
	close(1);
	pipe(g_pipe);
	return ;
}

void	redirect_3(char *filename)
{
	g_fd[0] = dup(0);
	g_fd[1] = dup(1);
	close(0);
	close(1);
	pipe(g_pipe);
	// dup2(g_fd_list->fd, g_pipe[0]);
	// dup2(g_fd_list->fd, g_pipe[1]);
	// close(g_fd_list->fd);
}
