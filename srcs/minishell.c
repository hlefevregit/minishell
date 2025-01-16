/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:09:12 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/15 19:10:04 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	}
	handle_redirection(cmd);
	get_cmd(cmd->name)(cmd);
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
		handle_redirection(cmd);
		get_cmd(cmd->name)(cmd);
		exit(EXIT_SUCCESS);
	}
	close(cmd->pipe[1]);
	if (node->prev)
		close(((t_cmd *)node->prev->content)->pipe[0]);
}
