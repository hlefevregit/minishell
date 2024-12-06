#include "../inc/minishell.h"

extern int	g_pid;

void	pipe_sigint(int signum)
{
	(void)signum;
	ft_printf("\n");
}

void	main_sigint(int signum)
{
	(void)signum;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_pid = 1;
}

void	main_sigquit(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
}

void	signals_main(void)
{
	signal(SIGINT, main_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_pipe(void)
{
	signal(SIGINT, pipe_sigint);
	signal(SIGQUIT, pipe_sigint);
}

