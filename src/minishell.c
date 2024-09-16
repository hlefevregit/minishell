/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:08:54 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/16 17:43:53 by hulefevr         ###   ########.fr       */
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
	int	i;
	free(mini.cmd);
	mini.infile = STDIN_FILENO;
	mini.outfile = STDOUT;
	// if (mini.token)
	// {
	// 	free(mini.token);
	// }
	if (mini.cmd_split)
	{
		i = -1;
		while (mini.cmd_split[++i])
		{
			printf("free mini.cmd_split[%d] = %s\n", i, mini.cmd_split[i]);
			if (mini.cmd_split[i])
				free(mini.cmd_split[i]);
		}
		free(mini.cmd_split);
		printf("free mini.cmd_split\n");
	}
	if (mini.isolate_cmd)
	{
		i = -1;
		printf("len of mini.isolate_cmd = %d\n", count_array(mini.isolate_cmd));
		while (mini.isolate_cmd[++i])
		{
			printf("free mini.isolate_cmd[%d] = %s\n", i, mini.isolate_cmd[i]);
			if (mini.isolate_cmd[i])
				free(mini.isolate_cmd[i]);
		}
		free(mini.isolate_cmd);
		printf("free mini.isolate_cmd\n");
	}
	return ;
}

t_mini	init_mini(char **envp)
{
	t_mini	mini;

	mini.envp = envp;
	mini.cmd = NULL;
	mini.cmd_split = NULL;
	mini.isolate_cmd = NULL;
	mini.infile = STDIN_FILENO;
	mini.outfile = STDOUT;
	mini.token = NULL;
	mini.num_tokens = 0;
	return (mini);
}

void	init_prompt(char **envp)
{
	t_mini mini;

	mini = init_mini(envp);
	while (1)
	{
		mini.cmd = readline(GREEN"MINISHELL DRUCKER A LA RESCOUSSE > "RESET);
		if (!mini.cmd)
			handle_ctrl_d();
		if (ft_strcmp(mini.cmd, "exit") == 0)
		{
			rl_clear_history();
			exit(0);
		}
		add_history(mini.cmd);
		if (mini.cmd[0] != 0)
			if (get_lex_of_cmd(mini) == -1)
				break ;
		// free_struct(mini);
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
