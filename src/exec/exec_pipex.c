/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:17:29 by hulefevr          #+#    #+#             */
/*   Updated: 2024/08/05 15:46:45 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_path_cmd(char *cmd)
{
	if (strncmp(cmd, "unset", 5) != 0 && ft_strncmp(cmd, "echo", 4) != 0)
		if (ft_strncmp(cmd, "cd", 2) != 0 && ft_strncmp(cmd, "export", 6) != 0)
			if (ft_strncmp(cmd, "pwd", 3) != 0 && ft_strncmp(cmd, "env", 3) != 0)
				return (0);
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
	else if (execve(cmd[0], cmd, mini.envp) == -1)
	{
		perror("execve");
		printf("command not found\n");
		return (-1);
	}
	return (0);
}

void	ft_execute(char *arg, t_mini mini)
{
	char	**cmd;

	if (!arg[0])
		return ;
	cmd = ft_split(arg, ' ');
	if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		exit(EXIT_SUCCESS);
	if (ft_execve(cmd, mini) == -1)
		g_global.exit_status = 127;
	free_double(cmd);
	return ;
}

void	ft_child_proc(char *av, t_mini mini)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		perror("Error fork \n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_execute(av, mini);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	ft_parent(t_mini mini)
{
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	dup2(mini.outfile, STDOUT_FILENO);
	ft_execute(mini.isolate_cmd[get_nb_cmd(mini) - 1], mini);
	dup2(saved_stdout, STDOUT_FILENO);
}

void	ft_exec_pipex(t_mini mini)
{
	int	i;

	i = 0;
	while (i < cntwrd(mini.cmd, 32))
	{
		if (mini.token[i].type == T_HEREDOC)
			here_doc(mini.token[i].value);
		else if (mini.token[i].type == T_I_FILE)
			mini.infile = open(mini.token[i].value, O_RDONLY, 0644);
		else if (mini.token[i].type == T_OR_FILE)
			mini.outfile = open(mini.token[i].value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (mini.token[i].type == T_OD_FILE)
			mini.outfile = open(mini.token[i].value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		// printf("mini.token[%i].type = %i\n", i, mini.token[i].type);
		i++;
	}
	// printf("infile = %i\nOutfile = %i\n", mini.infile, mini.outfile);
	while (i < get_nb_cmd(mini) - 2)
		ft_child_proc(mini.isolate_cmd[i++], mini);
	ft_parent(mini);
	ft_putstr_fd(GREEN"Done\n"RESET, 0);
}
