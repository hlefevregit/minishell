/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:17:29 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/23 18:07:26 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	execute_cmd(char *cmd, t_mini mini, int in_fd, int out_fd)
// {
// 	if (in_fd != STDIN)
// 	{
// 		dup2(in_fd, STDIN_FILENO);
// 		close(in_fd);
// 	}
// 	if (out_fd != STDOUT)
// 	{
// 		dup2(out_fd, STDOUT_FILENO);
// 		close(out_fd);
// 	}
// 	ft_execute(cmd, mini);
// }

// void	ft_child_proc(t_mini mini)
// {
// 	pid_t	pid;
// 	int		pipes[mini.num_cmd - 1][2];
// 	int		i;
// 	int		out_fd;
// 	int		in_fd;

// 	i = 0;
// 	while (i < mini.num_cmd - 1)
// 	{
// 		if (pipe(pipes[i]) == -1)
// 		{
// 			perror("pipe");
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < mini.num_cmd)
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pid == 0)
// 		{
// 			out_fd = STDOUT;
// 			in_fd = STDIN;
// 			out_fd = handle_out_redir(mini.isolate_cmd[i]);
// 			in_fd = handle_in_redir(mini.isolate_cmd[i]);
// 			if (i == 0)
// 			{
// 				close(pipes[i][0]);
// 				if (out_fd == STDOUT)
// 					out_fd = pipes[i][1];
// 				execute_cmd(mini.isolate_cmd[i], mini, mini.infile, out_fd);
// 			}
// 			else if (i == mini.num_cmd - 1)
// 			{
// 				close(pipes[i - 1][1]);
// 				execute_cmd(mini.isolate_cmd[i], mini, pipes[i - 1][0], out_fd);
// 			}
// 			else
// 			{
// 				close(pipes[i - 1][1]);
// 				close(pipes[i][0]);
// 				if (out_fd == STDOUT)
// 					out_fd = pipes[i][1];
// 				execute_cmd(mini.isolate_cmd[i], mini, pipes[i - 1][0], out_fd);
// 			}
// 		}
// 		else
// 		{
// 			waitpid(pid, NULL, 0);
// 		}
// int	ft_exec_pipex(t_mini mini)
// {
// 	// int	i;

	// i = 0;
	// while (i < cntwrd(mini.cmd, 32))
	// {
	// 	if (mini.token[i].type == T_HEREDOC)
	// 		here_doc(mini.token[i].value);
	// 	else if (mini.token[i].type == T_I_FILE)
	// 	{
	// 		mini.infile = open(mini.token[i].value, O_RDONLY, 0644);
	// 		if (mini.infile < 0)
	// 		{
	// 			perror("open");
	// 			exit(EXIT_FAILURE);
	// 		}
	// 	}
	// 	else if (mini.token[i].type == T_OR_FILE)
	// 	{
	// 		mini.outfile = open(mini.token[i].value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 		if (mini.outfile < 0)
	// 		{
	// 			perror("open");
	// 			exit(EXIT_FAILURE);
	// 		}
	// 	}
	// 	else if (mini.token[i].type == T_OD_FILE)
	// 	{
	// 		mini.outfile = open(mini.token[i].value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	// 		if (mini.outfile < 0)
	// 		{
	// 			perror("open");
	// 			exit(EXIT_FAILURE);
	// 		}
	// 	}
	// 	i++;
	// }
	// i = 0;
	// while (i < mini.num_cmd - 2)
	// ft_child_proc(mini);
	// printf("mini.num_cmd = %d\n", mini.num_cmd);
	// ft_parent(mini);
// 	ft_putstr_fd(GREEN"Done\n"RESET, 0);
// 	return (0);
// }
// 		i++;
// 	}
// 	i = 0;
// 	while (i < mini.num_cmd - 1)
// 	{
// 		close(pipes[i][0]);
// 		close(pipes[i][1]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < mini.num_cmd)
// 	{
// 		waitpid(pid, NULL, 0);
// 		i++;
// 	}
// }

// void	ft_parent(t_mini mini)
// {
// 	int		saved_stdout;

	
// 	saved_stdout = dup(STDOUT_FILENO);
// 	if (mini.outfile != STDOUT)
// 		dup2(mini.outfile, STDOUT_FILENO);
// 	printf("mini.num_cmd = %d\n", mini.num_cmd);
// 	ft_execute(mini.isolate_cmd[mini.num_cmd - 1], mini);
// 	dup2(saved_stdout, STDOUT_FILENO);
// }

int	handle_out_redir(char *cmd)
{
	int	out_fd;
	int	i;

	i = 0;
	out_fd = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>')
		{
			i++;
			if (cmd[i] == '>')
			{
				while (cmd[i] == ' ')
					i++;
				out_fd = open(&cmd[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (out_fd < 0)
				{
					perror("open");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				while (cmd[i] == ' ')
					i++;
				out_fd = open(&cmd[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (out_fd < 0)
				{
					perror("open");
					exit(EXIT_FAILURE);
				}
			}
			cmd[i] = '\0';
			break ;
		}
		else
			{
				out_fd = open(&cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (out_fd < 0)
				{
					perror("open");
					exit(EXIT_FAILURE);
				}
			}
			cmd[i] = '\0';
			break ;
		i++;
	}
	return (out_fd);
}

int	handle_in_redir(char *cmd)
{
	int	in_fd;
	int	i;

	i = 0;
	in_fd = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<')
		{
			i++;
			if (cmd[i] == '<')
			{
				while (cmd[i] == ' ')
					i++;
				here_doc(cmd + i);
				break ;
			}
			else
			{
				while (cmd[i] == ' ')
					i++;
				in_fd = open(&cmd[i], O_RDONLY, 0644);
				if (in_fd < 0)
				{
					perror("open");
					exit(EXIT_FAILURE);
				}
				cmd[i] = '\0';
				break ;
			}
		}
		i++;
	}
	return (in_fd);
}

void	ft_child_proc(char **av, t_mini mini)
{
	pid_t	pid;
	int		fd[2];
	int		i;
	int		prev_fd;

	i = 0;
	prev_fd = -1;
	if (mini.num_cmd == 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error fork \n");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			ft_execute(av[i], mini);
			exit(EXIT_SUCCESS);
		}
		else
			waitpid(pid, NULL, 0);
		return ;
	}
	while (i < mini.num_cmd - 1)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
		pid = fork();
		if (pid == -1)
		{
			perror("Error fork \n");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			
			if (i > 0)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (i < mini.num_cmd - 1)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			ft_execute(av[i], mini);
			printf("av[%d] = %s\n", i, av[i]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (i > 0)
				close(prev_fd);
			if (i < mini.num_cmd - 1)
			{
				close(fd[1]);
				prev_fd = fd[0];
			}
			waitpid(pid, NULL, 0);
		}
	}
}

int	ft_exec_pipex(t_mini mini)
{
	int	i;

	i = 0;
	ft_child_proc(mini.isolate_cmd, mini);
	ft_putstr_fd(GREEN"Done\n"RESET, 0);
	return (0);
}
