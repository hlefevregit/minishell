/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:08:54 by hulefevr          #+#    #+#             */
/*   Updated: 2024/08/01 18:00:18 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

t_global g_global;

void	handle(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("\b\b  \b\b");
		g_global.exit_status = 131;
		printf("Quit: 3\n");
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

void	init_prompt(char **envp)
{
	t_mini mini;

	mini.envp = envp;	
	g_global.exit_status = 0;
	while (1)
	{
		signal(SIGQUIT, handle);
		signal(SIGINT, handle);
		mini.cmd = readline(GREEN"MINISHELL DRUCKER A LA RESCOUSSE > "RESET);
		if (ft_strncmp(mini.cmd, "exit", 4) == 0)
		{
			clear_history();
			exit(EXIT_SUCCESS);
		}
		if (!mini.cmd)
		{
			printf(RED"EXIT\n"RESET);
			break ;
		}
		add_history(mini.cmd);
		get_lex_of_cmd(mini);
		free(mini.cmd);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	if (ac == 1)
		init_prompt(envp);
	return (0);
}
