/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:07:35 by hulefevr          #+#    #+#             */
/*   Updated: 2024/11/12 18:19:29 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (cmd->pipe)
		{
			dup2(cmd->out, 1);
			close(cmd->out);
		}
		if (cmd->in)
		{
			dup2(cmd->in, 0);
			close(cmd->in);
		}
		if (cmd->heredoc)
		{
			here_doc(cmd->limiter);
		}
		if (execve(cmd->cmd, cmd->args, NULL) == -1)
		{
			printf("minishell: %s: command not found\n", cmd->cmd);
			exit(127);
		}
	}
	else if (pid < 0)
	{
		printf("minishell: fork failed\n");
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

int	ft_builtins(t_cmd *s)
{
	if (!ft_strcmp(s->cmd, "echo"))
		ft_echo(s->args);
	else if (!ft_strcmp(s->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(s->cmd, "env"))
		ft_env(s->args);
	else if (!ft_strcmp(s->cmd, "export"))
		ft_export(s->args);
	else if (!ft_strcmp(s->cmd, "unset"))
		ft_unset(s->args);
	else if (!ft_strcmp(s->cmd, "cd"))
		ft_cd(s->args);
	else if (!ft_strcmp(s->cmd, "exit"))
		ft_exit(s->args);
	else
		return (0);
	return (1);
}

int	ft_exec(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd)
		{
			if (!ft_builtins(cmd))
				ft_execute(cmd);
		}
		ft_exec(cmd->next);
	}
	return (0);
}
