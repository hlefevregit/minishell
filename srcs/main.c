/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:18:33 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/15 19:10:00 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_pid;

void	wait_cmds(t_data *data)
{
	int		ret;
	t_list	*node;

	if (ft_lstsize(data->cmds) <= 1)
		return ;
	node = data->cmds->next;
	while (node)
	{
		waitpid(((t_cmd *)node->content)->pid, &ret, 0);
		ft_lstiter(((t_cmd *)node->content)->out, &close_redirection);
		node = node->next;
	}
	if (WIFEXITED(ret))
		g_pid = 0;
}

void	start_cmds(t_data *data)
{
	t_list		*node;

	node = data->cmds;
	while (node)
	{
		handle_heredoc(node->content);
		if (node->next)
			pipe_next(node);
		else
			pipe_prev(node);
		dup2(data->std_in, STDIN_FILENO);
		dup2(data->std_out, STDOUT_FILENO);
		node = node->next;
	}
	wait_cmds(data);
}

void	minishell(t_data *data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		free(line);
		signals_main();
		line = readline(GREEN"MINISHELL DRUCKER A LA RESCOUSSE > "RESET);
		if (!line)
		{
			free(line);
			free_data(data);
			printf(RED"exit\n"RESET);
			exit(1);
		}
		if (parse_input(data, line) != 1)
			continue ;
		add_history(line);
		signals_pipe();
		start_cmds(data);
		if (data->cmds)
			ft_lstclear(&data->cmds, &free_cmd);
		data->cmds = NULL;
	}
}

int	main(int ac, char **av, char **environ)
{
	t_data	*data;

	(void)ac;
	(void)av;
	g_pid = 0;
	data = init_data(environ);
	minishell(data);
	free_data(data);
}
