#ifndef REDIRECT_H
# define REDIRECT_H

int				g_fd[2];
int				g_pipe[2];
int				g_pipe_prev;
int				g_pipe_next;

/**
**	1 - ; 
**	2 - |
** 	3 - >
**	4 - >>
**	5 - <
**/

int		next_redirect(t_list *parse);

void	save_stdin_stdout(void);
int		open_stdin_stdout(void);

int		redirect_1(t_list *parse);
int		redirect_2(t_list *parse);
int		redirect_3(t_list *parse);
int		redirect_4(t_list *parse);
int		redirect_5(t_list *parse);

#endif