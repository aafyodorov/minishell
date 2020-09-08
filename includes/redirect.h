#ifndef REDIRECT_H
# define REDIRECT_H

#define	BUF_REDIR 10

typedef struct	s_fd
{
	int			fd;
	struct s_fd	*next;
	
}				t_fd;

t_fd			*g_fd_list;
t_fd			*g_fd_head;
int				g_fd[2];
int				g_pipe[2];
int				g_pipe_status[2];
//		g_pipe_status[0] - previous redirect
//		g_pipe_status[1] - next redirect

/**
**	1 - ; 
**	2 - |
** 	3 - >
**	4 - >>
**	5 - <
**/

void	read_pipe(t_fd **fd_list);

void	close_stdin_stdout(char *file);
void	open_stdin_stdout(void);
void	open_fd(t_list *parse, t_fd **fd_head, t_fd **fd_list);
void	close_fd(t_fd **fd_head);

void	redirect_1(char *func);
void	redirect_2(char *func);
void	redirect_3(char *file_name);
// void	redirect_4(char *file_name);
// void	redirect_5(char *func);

// void	redirect_1_close(void);
// void	redirect_2_close(void);
// void	redirect_3_close(void);
// void	redirect_4_close(void);
// void	redirect_5_close(void);

#endif
