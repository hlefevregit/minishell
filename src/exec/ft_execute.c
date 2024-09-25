/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:50:59 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/25 14:58:22 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	try_execve(char **cmd, t_mini mini)
{
	pid_t	pid;
	char	*path;
	int		status;

	path = find_path(cmd[0], mini.envp);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd[0], 2);
		g_global.exit_status = 127;
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(path);
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(path, cmd, mini.envp) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
			ft_putendl_fd(cmd[0], 2);
			exit(127);
		}
		else
			exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_global.exit_status = WEXITSTATUS(status);
	}
	free(path);
	return (1);
	
}

int	ft_execve(char **cmd, t_mini mini)
{
	if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
		ft_echo(cmd, mini);
	else if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
		ft_unset(cmd, mini);
	else if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
		ft_cd(cmd, mini);
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0)
		ft_export(cmd, mini);
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		ft_pwd(mini);
	else if (ft_strncmp(cmd[0], "env\0", 4) == 0)
		ft_env(cmd, mini);
	else
	{
		if (try_execve(cmd, mini) == 1)
			if (g_global.exit_status == 127)
				return (-1);
	}
	return (0);
}

void	ft_execute(char **arg, t_mini mini, int in_fd, int out_fd)
{
	handle_redirections(arg);
	
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (ft_execve(arg, mini) == -1)
	{
		printf("exit_status = %d\n", g_global.exit_status);
		exit(127);
	}
	exit(0);
}
