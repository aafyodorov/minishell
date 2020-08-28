#include <stdio.h>
#include <signal.h>
#include "minishell.h"

void	ctrl_c(int sig)
{
	// signal(SIGINT, SIG_IGN);
	return ;
}

void	signal_handler(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		g_exit_status = errno;
	return;
}