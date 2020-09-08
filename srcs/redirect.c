#include "libft.h"
#include "minishell.h"
#include "redirect.h"

void	redirect_1(t_list *parse)
{
	return ;
}

void	redirect_2(t_list *parse)
{
	g_fd[0] = dup(0);
	g_fd[1] = dup(1);
	close(0);
	close(1);
	pipe(g_pipe);
	return ;
}

static char	*get_filename(t_list *parse)
{

	while (parse && !(is_redirect(get_str(parse))))
		parse = parse->next;
	return (get_str(parse));
}

void	redirect_3(t_list *parse)
{
	const char	*filename = get_filename(parse);

	// g_fd[0] = dup(0);
	g_fd[1] = dup(1);
	// close(0);
	close(1);
	g_pipe[1] = open(filename, O_RDONLY | O_TRUNC | O_CREAT, 0777);
	// dup2(g_fd_list->fd, g_pipe[0]);
	// dup2(g_fd_list->fd, g_pipe[1]);
	// close(g_fd_list->fd);
}
