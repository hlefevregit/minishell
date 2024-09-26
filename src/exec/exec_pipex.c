/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:17:29 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/26 16:26:36 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redirections(char **cmd)
{
	int	i;
	int	fd;

	i = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<") == 0)
		{
			fd = open(cmd[i + 1], O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			cmd[i] = NULL;
			if (cmd[i + 1])
				cmd[i + 1] = NULL;
		}
		else if (ft_strcmp(cmd[i], ">") == 0)
		{
			fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			cmd[i] = NULL;
			if (cmd[i + 1])
				cmd[i + 1] = NULL;
		}
		else if (ft_strcmp(cmd[i], ">>") == 0)
		{
			fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			cmd[i] = NULL;
			if (cmd[i + 1])
				cmd[i + 1] = NULL;
		}
		else if (ft_strcmp(cmd[i], "<<") == 0)
		{
			here_doc(cmd[i + 1]);
			cmd[i] = NULL;
			if (cmd[i + 1])
				cmd[i + 1] = NULL;
		}
		i++;
	}
}

void	ft_child_proc(char **av, t_mini mini)
{
	pid_t	pid;
	int		fd[2];
	int		i;
	int		prev_fd;
	int		status;
	char	**last_cmd;

	i = 0;
	prev_fd = STDIN_FILENO;
	while (i < mini.num_cmd - 1)
	{
		printf("av[%d] = %s\n", i, av[i]);
		if (pipe(fd) == -1)
		{
			perror("Error pipe \n");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("Error fork \n");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			printf("child process\n");
			if (prev_fd != STDIN_FILENO)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}

			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			last_cmd = ft_split(av[i], 32);
			int exit_status = ft_execute(last_cmd, mini, prev_fd, STDOUT_FILENO);
			exit(exit_status);
		}
		else
		{
			printf("parent process\n");
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_global.exit_status = WEXITSTATUS(status);
			close(fd[1]);
			if (prev_fd != STDIN_FILENO)
				close(prev_fd);
			prev_fd = fd[0];
		}	
		i++;
	}
	last_cmd = ft_split(av[i], 32);
	ft_execute(last_cmd, mini, prev_fd, STDOUT_FILENO);
	free_double(last_cmd);
	// close(prev_fd);
}

int	ft_exec_pipex(t_mini mini)
{
	int	i;

	i = 0;
	ft_child_proc(mini.isolate_cmd, mini);
	printf("exit_status = %d\n", g_global.exit_status);
	ft_putstr_fd(GREEN"Done\n"RESET, 0);
	return (0);
}
