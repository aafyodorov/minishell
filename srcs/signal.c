#include <signal.h>
#include "minishell.h"

void	ctrl_c(int sig)
{
	ft_lstclear(&g_loc_vars, del_var_cont);
	free_args(&g_env_vars);
	exit(0);
}

//void	ctrl_

void	ctrl_d(void)
{
	printf("In ctrl_d\n");
	exit(0);
}

void	signal_handler(void)
{
	if (signal(SIGINT, ctrl_c) == SIG_ERR)
		g_exit_status = errno;
}