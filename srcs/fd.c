#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "minishell.h"
#include "redirect.h"

// t_fd	*ft_lstnew_fd(int fd)
// {5544
// 	t_fd *list;

// 	list = (t_fd *)ft_calloc(sizeof(t_fd), 1);
// 	if (list)
// 		list->fd = fd;
// 	return (list);
// }

// void	ft_lstadd_back_fd(t_fd **lst, t_fd *new)
// {
// 	t_fd *tmp;

// 	if (lst && *lst)
// 	{
// 		tmp = *lst;
// 		while (tmp->next != NULL)
// 			tmp = tmp->next;
// 		tmp->next = new;
// 	}
// 	else if (lst)
// 		*lst = new;
// }

// void	open_fd(t_list *parse, t_fd **fd_head, t_fd **fd_list)
// {
// 	int	i;
// 	int	fd;

// 	i = 0;
// 	while (parse)
// 	{
// 		i = is_redirect(get_str(parse));
// 		if (i == 3 || i == 4 || i == 5)
// 		{
// 			if (i == 3 && parse->next)
// 				fd = open(get_str(parse->next), O_RDONLY | O_TRUNC | O_CREAT, 0777);
// 			if (i == 4 && parse->next)
// 				fd = open(get_str(parse->next), O_RDONLY | O_APPEND | O_CREAT, 0777);
// 			if (i == 5 && parse->next)
// 				fd = open(get_str(parse->next), O_WRONLY, 0777);
// 			if (!*fd_head)
// 				*fd_head = ft_lstnew_fd(fd);
// 			else
// 				ft_lstadd_back_fd(fd_head, ft_lstnew_fd(fd));
// 		}
// 		parse = parse->next;
// 	}
// 	*fd_list = *fd_head;
// }

// void	close_fd(t_fd **fd_head)
// {
// 	t_fd	*tmp;

// 	while (*fd_head)
// 	{
// 		tmp = (*fd_head)->next;
// 		close((*fd_head)->fd);
// 		free(*fd_head);
// 		*fd_head = tmp;
// 	}
// }
// 
// char	*get_args_from_pipe(void)
// {
// 	char	*line;
// 	char	*tmp;
// 	char	*res;

// 	res = NULL;
// 	while ((get_next_line(g_pipe[0], &line)) > 0) //??????? как фд ???????
// 	{
// 		if (!res)
// 			res = ft_strjoin("", line);
// 		else
// 		{
// 			tmp = res;
// 			res = ft_strjoin(res, line);
// 			free_str(&tmp) + free_str(&line);
// 		}
// 	}
// 	return (res);
// }

void	save_stdin_stdout(void)
{
	g_fd[0] = dup(0);
	g_fd[1] = dup(1);

}

int		open_stdin_stdout(void)
{
	// if (g_pipe_next >= 3) //????????????
	dup2(g_fd[1], 1);
	// dup2(g_fd[0], 0);
	return (0);
}