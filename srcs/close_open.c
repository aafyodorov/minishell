#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"

void	close_stdin_stdout(char *file)
{
	g_fd[0] = dup(0);
	g_fd[1] = dup(1);
	close(0);
	close(1);
	g_fd[2] = open(file, O_RDONLY | O_TRUNC | O_CREAT, 0777);
	g_fd[3] = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	g_fd[4] = 1;
}

void	open_stdin_stdout(void)
{
	close(g_fd[2]);
	close(g_fd[3]);
	dup2(g_fd[0], 0);
	dup2(g_fd[1], 1);
	close(g_fd[0]);
	close(g_fd[1]);
}