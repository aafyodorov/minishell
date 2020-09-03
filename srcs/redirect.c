#include "minishell.h"

/**
 * 0 - not redirect
 * 1 - ;
 * 2 - |
 * 3 - >
 * 4 - >>
 * 5 - <
**/

void	redirect_1(void)
{
	return ;
}

void	redirect_1_close(void)
{
	return ;
}

void	redirect_2(void)
{
	pipe(g_pipe);				// открываем pipe
	g_fd[0] = dup(0);			// сохраняем stdin
	dup2(0, g_pipe[0]);			// открываем pipe[0] вместо stdin
	g_fd[1] = dup(1);			// сохраняем stdout
	dup2(1, g_pipe[1]);			// открываем pipe[1] вместо stdout
	g_pipe_status[1] = 2;		// g_pipe_status[1] при проверке говорит нам, что до этого был |
	return ;
}

void	redirect_2_close(void)
{
	dup2(g_fd[0], 0);
	dup2(g_fd[1], 1);
	g_pipe_status[1] = 0;
}

void	redirect_3(void)
{
	return ;
}

void	redirect_3_close(void)
{
	return ;
}

void	redirect_4(void)
{
	return ;
}

void	redirect_4_close(void)
{
	return ;
}

void	redirect_5(void)
{
	return ;
}

void	redirect_5_close(void)
{
	return ;
}