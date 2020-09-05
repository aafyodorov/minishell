#include <signal.h>
#include "minishell.h"

void	ctrl_c(int sig)
{
	write(1, "\n\r", 2);
	show_prompt();
}

//void	ctrl_

void	ctrl_d(void)
{
	free_args(&g_env_vars);
	ft_lstclear(&g_loc_vars, del_var_cont);
	printf("In ctrl_D\n");
	exit(0);
}

void	signal_handler(void)
{
	if (signal(SIGINT, ctrl_c) == SIG_IGN)
	{
		printf("!!!!!!!!!!!!");
		g_exit_status = errno;
	}
}