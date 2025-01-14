/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:18:33 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/06 15:49:57 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_pid;

void	print_cmd(void *ptr)
{
	t_cmd	*lexer;
	int		i;

	i = 0;
	lexer = ptr;
	printf("Command '%s':\n -> Args:\n", lexer->name);
	while (lexer->args[i])
		printf("  -> [%s]\n", lexer->args[i++]);
}

t_func_cmd	get_cmd(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (&ft_echo);
	if (!ft_strcmp(name, "cd"))
		return (&ft_cd);
	if (!ft_strcmp(name, "pwd"))
		return (&ft_pwd);
	if (!ft_strcmp(name, "unset"))
		return (&ft_unset);
	if (!ft_strcmp(name, "env"))
		return (&ft_env);
	if (!ft_strcmp(name, "export"))
		return (&ft_export);
	if (!ft_strcmp(name, "exit"))
		return (&ft_exit);
	return (&ft_execve);
}

int	open_options(t_token token)
{
	if (token == T_OUT_APPEND)
		return (O_WRONLY | O_APPEND | O_CREAT);
	if (token == T_OUT_TRUNCATE)
		return (O_WRONLY | O_TRUNC | O_CREAT);
	if (token == T_IN)
		return (O_RDONLY);
	return (0);
}

void	handle_redirection(void *ptr)
{
	t_lexer	*content;

	content = ptr;
	if (content->token == T_HERE_DOC)
		here_doc(content->str);
	content->fd = open(content->str, open_options(content->token), 0777);
	if (content->fd < 0)
	{
		dprintf(2, "minishell: no such file or directory: %s\n", content->str);
		return ;
	}
	dup2(content->fd, content->token != T_IN);
}

void	close_redirection(void *ptr)
{
	t_lexer	*content;

	content = ptr;
	close(content->fd);
}

void	pipe_prev(t_list *node)
{
	t_cmd	*prev_cmd;
	t_cmd	*cmd;

	cmd = node->content;
	if (node->prev)
	{
		prev_cmd = node->prev->content;
		dup2(prev_cmd->pipe[0], STDIN_FILENO); 
		close(prev_cmd->pipe[0]);
		close(prev_cmd->pipe[1]); 
	}
	if (cmd->out)
		ft_lstiter(cmd->out, &handle_redirection);
	cmd->pid = fork();
	if (cmd->pid == 0) 
	{
		get_cmd(cmd->name)(cmd);
		exit(EXIT_SUCCESS);
	}
}

void	pipe_next(t_list *node)
{
	t_cmd	*cmd;

	cmd = node->content;
	pipe(cmd->pipe); 
	cmd->pid = fork();

	if (cmd->pid == 0)
	{
		dup2(cmd->pipe[1], STDOUT_FILENO); 
		close(cmd->pipe[0]); 
		close(cmd->pipe[1]);
		if (node->prev)
		{
			dup2(((t_cmd *)node->prev->content)->pipe[0], STDIN_FILENO); 
			close(((t_cmd *)node->prev->content)->pipe[0]);
		}
		if (cmd->out)
			ft_lstiter(cmd->out, &handle_redirection);
		get_cmd(cmd->name)(cmd);
		exit(EXIT_SUCCESS);
	}
	close(cmd->pipe[1]);
	if (node->prev)
		close(((t_cmd *)node->prev->content)->pipe[0]); 
}

void	start_cmds(t_data *data)
{
	t_list		*node;
	int			ret;

	node = data->cmds;
	while (node)
	{
		if (node->next)
			pipe_next(node); 
		else
			pipe_prev(node); 
		dup2(data->std_in, STDIN_FILENO);
		dup2(data->std_out, STDOUT_FILENO);
		node = node->next;
	}
	node = data->cmds;
	while (node)
	{
		waitpid(((t_cmd *)node->content)->pid, &ret, 0);
		ft_lstiter(((t_cmd *)node->content)->out, &close_redirection);
		node = node->next;
	}
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
