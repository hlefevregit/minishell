/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:42:28 by marvin            #+#    #+#             */
/*   Updated: 2022/08/10 19:42:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exit_condition(char *l)
{
	if (!l || ft_strcmp(l, "exit") == 0
		|| (ft_strncmp(l, "exit", 4) == 0 && !ft_isprint(l[4])
			&& !ft_strchr(l, '|'))
		|| ft_strncmp(l, "\"exit\"", 6) == 0
		|| ft_strncmp(l, "\'exit\'", 6) == 0)
		return (1);
	return (0);
}

void	loop_prompt(t_list *list)
{
	char	*line;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		line = readline(PROMPT);
		if (ft_strlen(line))
			add_history(line);
		if (line && (get_quote(line) || is_empty(line)))
			continue ;
		else if (exit_condition(line) == 1)
			exit(EXIT_SUCCESS);
		else if (line[0] == 0 || ft_isspace(line))
			continue ;
		
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*list;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_interr);
	list = init_list(envp);
	loop_prompt(list);
	return (0);
}