/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:50:59 by hulefevr          #+#    #+#             */
/*   Updated: 2024/11/25 17:18:26 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	try_execve(char **cmd, t_mini mini)
{
	char	*path;
	int		status;
	pid_t	pid;

	path = find_path(cmd[0], mini.envp);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd[0], 2);
		g_global.exit_status = 127;
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, cmd, mini.envp) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
			ft_putendl_fd(cmd[0], 2);
			exit(127);
		}
	}	
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_global.exit_status = WEXITSTATUS(status);
	}
	free(path);
	return (g_global.exit_status);
	
}

int	ft_is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

void	ft_exec_builtin(char **cmd, t_mini mini)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd, mini);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd, mini);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd(mini);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(cmd, mini);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(cmd, mini);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(cmd, mini);
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		g_global.exit_status = ft_exit(cmd, mini);
		exit (g_global.exit_status % 256);
	}
}
void	remove_args(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (ft_strcmp(arg[i], ">") == 0 || ft_strcmp(arg[i], ">>") == 0)
		{
			arg[i] = NULL;
			arg[i + 1] = NULL;
			break ;
		}
		i++;
	}
	return ;
}

int	handle_in_redir(char **arg)
{
	int		i;
	int		fd;

	i = 0;
	while (arg[i])
	{
		if (ft_strncmp(arg[i], "<", 1) == 0)
		{
			if (arg[i + 1] == NULL)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `newline'", STDERR_FILENO);
				return (STDIN_FILENO);
			}
			fd = open(arg[i + 1], O_RDONLY);
			if (fd == -1)
				return (-1);
			i--;
			arg[i] = NULL;
			arg[i + 1] = NULL;
			return (fd);
		}
		i++;
	}
	return (STDIN_FILENO);
}

int	handle_out_redir(char **arg)
{
	int		i;
	int		fd;

	i = 0;
	while (arg[i])
	{
		if (ft_strncmp(arg[i], ">", 1) == 0)
		{
			if (arg[i + 1] == NULL)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `newline'", STDERR_FILENO);
				return (STDOUT_FILENO);
			}
			if (ft_strncmp(arg[i], ">>", 2) == 0)
				fd = open(arg[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd = open(arg[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			i--;
			while (arg[i++])
				arg[i] = NULL;
			remove_args(arg);
			return (fd);
		}
		i++;
	}
	remove_args(arg);
	return (STDOUT_FILENO);
}

void	handle_here_doc(char **arg)
{
	int		i;
	
	i = 0;
	while (arg[i])
	{
		if (ft_strncmp(arg[i], "<<", 2) == 0)
		{
			arg[i] = NULL;
			i++;
			if (arg[i] == NULL)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `newline'", STDERR_FILENO);
				return ;
			}
			here_doc(arg[i]);
			arg[i] = NULL;
			return ;
		}
		i++;
	}
}

int	ft_execute(char **arg, t_mini mini, int in_fd, int out_fd)
{
	int		exit_status;


	(void)in_fd;
	(void)out_fd;
	if (!arg || !arg[0])
		return (-1);
	// in_fd = handle_in_redir(arg);
	// out_fd = handle_out_redir(arg);
	// int i = -1;
	// while (arg[++i])
	// 	printf("arg[%d]: %s\n", i, arg[i]);
	// if (in_fd != STDIN_FILENO)
	// 	dup2(in_fd, STDIN_FILENO);
	// if (out_fd != STDOUT_FILENO)
	// 	dup2(out_fd, STDOUT_FILENO);
	else
	{
		exit_status = try_execve(arg, mini);
		if (exit_status == 127)
			return (127);
	}
	return (g_global.exit_status);
}
