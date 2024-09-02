/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:08:54 by hulefevr          #+#    #+#             */
/*   Updated: 2024/08/27 15:50:14 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

t_global g_global;

void	handle(int sig)
{
	if (sig == SIGQUIT)
	{
		g_global.exit_status = 131;
		printf("Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.exit_status = 130;
	}
}

void	handle_ctrl_d(void)
{
	printf(RED"Exit\n"RESET);
	rl_clear_history();
	exit(0);
}

void	free_struct(t_mini mini)
{
	free(mini.cmd);
	mini.infile = STDIN_FILENO;
	mini.outfile = STDOUT;
	return ;
}

void	init_prompt(char **envp)
{
	t_mini mini;

	mini.envp = envp;	
	g_global.exit_status = 0;
	while (1)
	{
		mini.cmd = readline(GREEN"MINISHELL DRUCKER A LA RESCOUSSE > "RESET);
		if (!mini.cmd)
			handle_ctrl_d();
		if (ft_strcmp(mini.cmd, "exit") == 0)
		{
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}
		add_history(mini.cmd);
		get_lex_of_cmd(mini);
		free_struct(mini);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	signal(SIGQUIT, handle);
	signal(SIGINT, handle);
	if (ac == 1)
		init_prompt(envp);
	return (0);
}
