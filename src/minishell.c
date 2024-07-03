/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:08:54 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/03 14:16:25 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../includes/minishell.h"

void	init_prompt(char **envp)
{
	t_mini mini;

	mini.envp = envp;
	mini.num_of_pipe = 0;
	while (1)
	{
		mini.cmd = readline(GREEN"MINISHELL DRUCKER A LA RESCOUSSE > "RESET"");
		if (ft_strncmp(mini.cmd, "exit", 4) == 0)
		{
			rl_clear_history();
			exit(EXIT_SUCCESS);
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
