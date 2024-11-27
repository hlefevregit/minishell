/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:17:29 by hulefevr          #+#    #+#             */
/*   Updated: 2024/11/27 15:52:49 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_pipes(t_mini mini, int i)
{
	if (i >= 1)
	{
		dup2(mini.pipefd[i - 1][0], STDIN_FILENO);
		close(mini.pipefd[i - 1][0]);
		close(mini.pipefd[i - 1][1]);
	}
	if (i < mini.num_cmd - 1)
	{
		dup2(mini.pipefd[i][1], STDOUT_FILENO);
		close(mini.pipefd[i][0]);
		close(mini.pipefd[i][1]);
	}
}

void	close_pipe(t_mini mini, int i)
{
	if (i >= 1)
	{
		close(mini.pipefd[i - 1][0]);
		close(mini.pipefd[i - 1][1]);
	}
}

int	is_only_space(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			j++;
		i++;
	}
	if (j == i)
		return (0);
	return (1);
}

void	ft_child_proc(char **av, t_mini mini)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < mini.num_cmd)
	{
		printf("av[%d] = %s\n", i, av[i]);
		if (i < mini.num_cmd -1)
			pipe(mini.pipefd[i]);
		if (!is_only_space(av[i]))
			continue ;
		if (ft_is_builtin(ft_split(av[i], 32)[0]) == 1)
		{
			int saved_stdout = dup(STDOUT_FILENO);
			int out_fd = handle_out_redir(ft_split(av[i], 32));
			char **cmd = ft_split(av[i], 32);
			cmd = remove_args(cmd);
			ft_exec_builtin(cmd, mini);
			if (out_fd != STDOUT_FILENO)
			{
				dup2(saved_stdout, STDOUT_FILENO);
				close(saved_stdout);
			}
			free_double(cmd);
			continue ;
		}
		handle_here_doc(ft_split(av[i], 32));
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			dup_pipes(mini, i);
			if (mini.num_cmd == 1)
				exit(ft_execute(ft_split(av[i], 32), mini, mini.infile, mini.outfile));
			else
				exit(ft_execute(ft_split(av[i], 32), mini, mini.pipefd[i][0], mini.pipefd[i][1]));
		}
		if (i == mini.num_cmd - 1)
			waitpid(pid, &g_global.exit_status, 0);
		g_global.exit_status = WEXITSTATUS(g_global.exit_status);
		printf("exit status: %d\n", g_global.exit_status);
		close_pipe(mini, i);
	}
	
}

// void	ft_child_proc(char **arg, t_mini mini)
// {
// 	pid_t	child1;
// 	pid_t	child2;
// 	int		pipefd[2];
// 	int		i;

// 	i = 1;
// 	if (mini.num_cmd == 1)
// 	{
// 		printf("salut\n");
// 		if (ft_is_builtin(ft_split(arg[0], 32)[0]) == 1)
// 		{
// 			int saved_stdout = dup(STDOUT_FILENO);
// 			int out_fd = handle_out_redir(ft_split(arg[0], 32));
// 			char **cmd = ft_split(arg[0], 32);
// 			cmd = remove_args(cmd);
// 			ft_exec_builtin(cmd, mini);
// 			if (out_fd != STDOUT_FILENO)
// 			{
// 				dup2(saved_stdout, STDOUT_FILENO);
// 				close(saved_stdout);
// 			}
// 		}
// 		else
// 		{
// 			child1 = fork();
// 			if (child1 == 0)
// 				exit(ft_execute(ft_split(arg[0], 32), mini));
// 		}
// 	}
// 	else
// 	{
// 		pipe(pipefd);
// 		child1 = fork();
// 		if (child1 == 0)
// 		{
// 			dup2(pipefd[1], STDOUT_FILENO);
// 			close(pipefd[0]);
// 			close(pipefd[1]);
// 			mini.num_cmd = 1;
// 			ft_child_proc(&arg[i], mini);
// 			exit(g_global.exit_status);
// 		}
// 		child2 = fork();
// 		if (child2 == 0)
// 		{
// 			dup2(pipefd[0], STDIN_FILENO);
// 			close(pipefd[0]);
// 			close(pipefd[1]);
// 			ft_child_proc(&arg[i++], mini);
// 			exit(g_global.exit_status);
// 		}
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 		waitpid(child1, &g_global.exit_status, 0);
// 		waitpid(child2, &g_global.exit_status, 0);
// 		g_global.exit_status = WEXITSTATUS(g_global.exit_status);
// 	}
// }

int	ft_exec_pipex(t_mini mini)
{
	int		i;

	i = -1;
	while (++i < mini.num_cmd -1)
		mini.pipefd[i] = malloc(sizeof(int) * 2);
	ft_child_proc(mini.isolate_cmd, mini);
		i = -1;
	while (++i < mini.num_cmd -1)
		free(mini.pipefd[i]);
	return (0);
}
