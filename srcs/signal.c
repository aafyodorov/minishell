#include <signal.h>
#include "minishell.h"

void	ctrl_c(int sig)
{
	ft_printf("Got signal %d\n", sig);
	exit(0);
}

void	ctrl_d(void)
{
	printf("In ctrl_d\n");
	ft_lstclear(&g_loc_vars, del_var_cont);
	exit(0);
}

void	signal_handler(void)
{
	if (signal(SIGINT, ctrl_c) == SIG_ERR)
		g_exit_status = errno;
	return;
}