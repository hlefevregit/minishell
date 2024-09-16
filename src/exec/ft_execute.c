/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:50:59 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/16 19:12:21 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	try_execve(char **cmd, t_mini mini)
{
	pid_t	pid;
	char	*path;
	int		status;

	pid = fork();
	path = find_path(cmd[0], mini.envp);
	if (pid <= 0)
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
	else if (try_execve(cmd, mini) == 1)
	{
		if (g_global.exit_status == 127)
			return (-1);
	}
	g_global.exit_status = 0;
	return (0);
}

void	ft_execute(char *arg, t_mini mini)
{
	char	**cmd;
	int		i;

	if (!arg[0])
		return ;
	cmd = ft_split(arg, ' ');
	for (int j = 0; j < cntwrd(arg, 32); j++)
		printf("cmd[%i] = %s\n", j, cmd[j]);
	if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		exit(EXIT_SUCCESS);
	if (ft_execve(cmd, mini) == -1)
	{
		printf(RED"->"RESET);
		return ;
	}
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i])
		{
			free(cmd[i]);
			printf("free cmd[%d]\n", i);
		}
	}
	if (cmd)
		free(cmd);
	return ;
}
