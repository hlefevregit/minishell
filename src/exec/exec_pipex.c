/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:17:29 by hulefevr          #+#    #+#             */
/*   Updated: 2024/11/22 14:57:30 by hulefevr         ###   ########.fr       */
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


void	dup_pipes(t_mini mini, int index)
{
	if (index >= 1)
	{
		dup2(mini.pipefd[index - 1][0], STDIN_FILENO);
		close(mini.pipefd[index - 1][0]);
		close(mini.pipefd[index - 1][1]);
	}
	if (index < mini.num_cmd - 1)
	{
		dup2(mini.pipefd[index][1], STDOUT_FILENO);
		close(mini.pipefd[index][0]);
		close(mini.pipefd[index][1]);
	}
}

void	close_pipe(t_mini mini, int index)
{
	if (index >= 1)
	{
		close(mini.pipefd[index - 1][0]);
		close(mini.pipefd[index - 1][1]);
	}
	// if (index < mini.num_cmd - 1)
	// {
	// 	close(mini.pipefd[index][0]);
	// 	close(mini.pipefd[index][1]);
	// }
}

void	ft_child_proc(char **av, t_mini mini)
{
	// int	fd[2];
	// int fdd;
	pid_t	pid;
	// int		status;
	int		index;

	index = -1;
	while (++index < mini.num_cmd)
	{
		if (index < mini.num_cmd -1)
			pipe(mini.pipefd[index]);
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			dup_pipes(mini, index);		
			exit(ft_execute(ft_split(av[index], 32), mini, mini.pipefd[index][0], mini.pipefd[index][1]));
		}
		close_pipe(mini, index);
		// else
		// {
		// 	waitpid(pid, &status, 0);
		// 	g_global.exit_status = WEXITSTATUS(status);
		// 	close(fd[1]);
		// 	fdd = fd[0];
		// }
	}
	
}

int	ft_exec_pipex(t_mini mini)
{
	int	i;

	i = 0;
	while (i < mini.num_cmd)
	{
		mini.pipefd[i] = malloc(sizeof(int) * 2);
		if (!mini.pipefd[i])
			return (-1);
		i++;
	}
	ft_child_proc(mini.isolate_cmd, mini);
	// printf("exit_status = %d\n", g_global.exit_status);
	// ft_putstr_fd(GREEN"Done\n"RESET, 0);
	// usleep(7000);
	return (0);
}
