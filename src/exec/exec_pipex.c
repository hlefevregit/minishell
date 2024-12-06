/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:17:29 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/06 15:20:59 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	dup_pipes(t_mini mini, int i)
// {
// 	if (i >= 1)
// 	{
// 		dup2(mini.pipefd[i - 1][0], STDIN_FILENO);
// 		close(mini.pipefd[i - 1][0]);
// 		close(mini.pipefd[i - 1][1]);
// 	}
// 	if (i < mini.num_cmd - 1)
// 	{
// 		dup2(mini.pipefd[i][1], STDOUT_FILENO);
// 		close(mini.pipefd[i][0]);
// 		close(mini.pipefd[i][1]);
// 	}
// }

// void	close_pipe(t_mini mini, int i)
// {
// 	if (i >= 1)
// 	{
// 		close(mini.pipefd[i - 1][0]);
// 		close(mini.pipefd[i - 1][1]);
// 	}
// }

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

// void	ft_child_proc(char **av, t_mini mini)
// {
// 	pid_t	pid;
// 	int		i;

// 	i = -1;
// 	while (++i < mini.num_cmd)
// 	{
// 		// printf("av[%d] = %s\n", i, av[i]);
// 		char **cmd = ft_split(av[i], 32);
// 		if (i < mini.num_cmd -1)
// 			pipe(mini.pipefd[i]);
// 		if (!is_only_space(av[i]))
// 			continue ;
// 		if (ft_is_builtin(cmd[0]) == 1)
// 		{
// 			int saved_stdout = dup(STDOUT_FILENO);
// 			int out_fd = handle_out_redir(cmd);
// 			cmd = remove_args(cmd);
// 			ft_exec_builtin(cmd, mini);
// 			if (out_fd != STDOUT_FILENO)
// 			{
// 				dup2(saved_stdout, STDOUT_FILENO);
// 				close(saved_stdout);
// 				close(out_fd);
// 			}
// 			// int i = -1;
// 			// while (cmd[++i])
// 			// 	printf("cmd[%d] = %s\n", i, cmd[i]);	
// 			if (cmd)
// 				free_double(cmd);
// 			continue ;
// 		}
// 		handle_here_doc(cmd);
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pid == 0)
// 		{
// 			dup_pipes(mini, i);
// 			if (mini.num_cmd == 1)
// 				exit(ft_execute(cmd, mini, mini.infile, mini.outfile));
// 			else
// 				exit(ft_execute(cmd, mini, mini.pipefd[i][0], mini.pipefd[i][1]));
// 		}
// 		if (i == mini.num_cmd - 1)
// 			waitpid(pid, &g_global.exit_status, 0);
// 		g_global.exit_status = WEXITSTATUS(g_global.exit_status);
// 		// printf("exit status: %d\n", g_global.exit_status);
// 		close_pipe(mini, i);
// 		free_double(cmd);
// 	}
	
// }

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

// int	ft_exec_pipex(t_mini mini)
// {
// 	int		i;

// 	i = -1;
// 	while (++i < mini.num_cmd -1)
// 		mini.pipefd[i] = malloc(sizeof(int) * 2);
// 	ft_child_proc(mini.isolate_cmd, mini);
// 		i = -1;
// 	while (++i < mini.num_cmd -1)
// 		free(mini.pipefd[i]);
// 	return (0);
// }

void	ft_builtin_parse(t_token *token, t_mini mini)
{
	handle_redirections(token);
	if (ft_strcmp(token[0].value, "cd") == 0)
		ft_cd(token, mini);
	else if (ft_strcmp(token[0].value, "echo") == 0)
		ft_echo(token, mini);
	else if (ft_strcmp(token[0].value, "pwd") == 0)
		ft_pwd(mini);
	else if (ft_strcmp(token[0].value, "unset") == 0)
		ft_unset(token, mini);
	else if (ft_strcmp(token[0].value, "export") == 0)
		ft_export(token, mini);
	else if (ft_strcmp(token[0].value, "env") == 0)
		ft_env(token, mini);
	else if (ft_strcmp(token[0].value, "exit") == 0)
	{
		g_global.exit_status = ft_exit(token, mini);
		exit (g_global.exit_status % 256);
	}
}

void	exec_pipes(t_mini mini, int i)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];

	if (mini.cmd[i].is_pipe == 0)
	{
		if (ft_is_builtin(mini.cmd[i].token[0].value) == 1)
			ft_builtin_parse(mini.cmd[i].token, mini);
		else
			ft_child_proc(mini.cmd[i].token, mini);
	}
	else
	{
		pipe(pipefd);
		pid1 = fork();
		if (pid1 == 0)
		{
			dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[0]);
			close(pipefd[1]);
			cmd[i].is_pipe = 0;
            execute_pipes(mini, i);
            exit(0);
		}
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			execute_pipes(mini, i++);
			exit(0);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
}

void	transfer_tokens(t_mini mini)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	mini.cmd = malloc(sizeof(t_cmd) * mini.num_cmd);
	while (i < mini.num_cmd)
	{
		mini.cmd[i].token = malloc(sizeof(t_token) * mini.num_tokens);
		while (j < mini.num_tokens)
		{
			mini.cmd[i].token[j] = mini.token[k];
			j++;
			k++;
		}
		mini.cmd[i].token[j].type = T_END;
		j = 0;
		i++;
	}
	return ;
}

int	ft_exec_pipex(t_mini mini)
{
	if (mini.num_cmd == 1)
		exec_single_cmd(mini);
	else
	{
		transfer_tokens(mini);
		mini.cmd.is_pipe = 1;
		exec_pipes(mini, 0);
	}
}