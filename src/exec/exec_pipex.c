/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:17:29 by hulefevr          #+#    #+#             */
/*   Updated: 2024/11/22 13:06:25 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	handle_redirections(char **cmd)
// {
// 	int	i;
// 	int	fd;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (ft_strcmp(cmd[i], "<") == 0)
// 		{
// 			fd = open(cmd[i + 1], O_RDONLY);
// 			if (fd < 0)
// 			{
// 				perror("open");
// 				exit(EXIT_FAILURE);
// 			}
// 			dup2(fd, STDIN_FILENO);
// 			close(fd);
// 			cmd[i] = NULL;
// 			if (cmd[i + 1])
// 				cmd[i + 1] = NULL;
// 		}
// 		else if (ft_strcmp(cmd[i], ">") == 0)
// 		{
// 			fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd < 0)
// 			{
// 				perror("open");
// 				exit(EXIT_FAILURE);
// 			}
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 			cmd[i] = NULL;
// 			if (cmd[i + 1])
// 				cmd[i + 1] = NULL;
// 		}
// 		else if (ft_strcmp(cmd[i], ">>") == 0)
// 		{
// 			fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (fd < 0)
// 			{
// 				perror("open");
// 				exit(EXIT_FAILURE);
// 			}
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 			cmd[i] = NULL;
// 			if (cmd[i + 1])
// 				cmd[i + 1] = NULL;
// 		}
// 		else if (ft_strcmp(cmd[i], "<<") == 0)
// 		{
// 			here_doc(cmd[i + 1]);
// 			cmd[i] = NULL;
// 			if (cmd[i + 1])
// 				cmd[i + 1] = NULL;
// 		}
// 		i++;
// 	}
// 	return ;
// }

void	ft_child_proc(char **av, t_mini mini, int i)
{
	int	fd[2];
	int fdd;
	pid_t	pid;
	int		status;

	fdd = 0;
	while (av[i])
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			dup2(fdd, 0);
			if (av[i + 1])
				dup2(fd[1], 1);
			close(fd[0]);
			exit (ft_execute(ft_split(av[i], 32), mini, 0, 1));
		}
		else
		{
			waitpid(pid, &status, 0);
			g_global.exit_status = WEXITSTATUS(status);
			close(fd[1]);
			fdd = fd[0];
			i++;
		}
	}
	
}

int	ft_exec_pipex(t_mini mini)
{
	int	i;

	i = 0;
	ft_child_proc(mini.isolate_cmd, mini, 0);
	printf("exit_status = %d\n", g_global.exit_status);
	ft_putstr_fd(GREEN"Done\n"RESET, 0);
	return (0);
}
