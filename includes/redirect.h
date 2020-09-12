#ifndef REDIRECT_H
# define REDIRECT_H

#define	BUF_REDIR 10

// typedef struct	s_fd
// {
// 	int			fd;
// 	struct s_fd	*next;
	
// }				t_fd;

// t_fd			*g_fd_list;
// t_fd			*g_fd_head;
int				g_fd[2];
int				g_pipe[2];
int				g_pipe_prev;
int				g_pipe_next;
//		g_pipe_prev - previous redirect


/**
**	1 - ; 
**	2 - |
** 	3 - >
**	4 - >>
**	5 - <
**/

int		next_redirect(t_list *parse);

void	save_stdin_stdout(void);

int		close_stdin(void);
int		open_stdin(void);
int		close_stdout(void);
int		open_stdout(void);

int		open_stdin_stdout(void);

int		redirect_1(t_list *parse);
int		redirect_2(t_list *parse);
int		redirect_3(t_list *parse);
int		redirect_4(t_list *parse);
int		redirect_5(t_list *parse);

#endif
