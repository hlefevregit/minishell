/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:50:59 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/02 18:24:31 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	try_execve(char **cmd, t_mini mini)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	path = find_path(cmd[0], mini.envp);
	if (pid <= 0)
	{
		if (execve(path, cmd, mini.envp) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
			ft_putendl_fd(cmd[0], 2);
			g_global.exit_status = 127;
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, NULL, 0);
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
		g_global.exit_status = 0;
	else 
		return (-1);
	return (0);
}

void	ft_execute(char *arg, t_mini mini)
{
	char	**cmd;

	if (!arg[0])
		return ;
	cmd = ft_split(arg, ' ');
	for (int j = 0; j < cntwrd(arg, 32); j++)
		printf("cmd[%i] = %s\n", j, cmd[j]);
	if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		exit(EXIT_SUCCESS);
	if (ft_execve(cmd, mini) == -1)
		printf(RED"->"RESET);
	free_double(cmd);
	return ;
}
