/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:08:54 by hulefevr          #+#    #+#             */
/*   Updated: 2024/06/12 16:47:01 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../includes/minishell.h"

/*void	get_var_name(t_mini mini)
{
	
}*/

void	search_for_args(t_mini mini)
{
	int	i;

	i = -1;
	printf("\n");
	while (++i < cntwrd(mini.cmd, 32))
	{
		if (mini.token[i].type == T_DLESS && mini.token[i + 1].type == T_ERR)
			mini.token[i + 1].type = T_HEREDOC;
		else if (mini.token[i].type == T_CMD)
		{
			while (mini.token[i + 1].type == T_ERR)
			{
				mini.token[i + 1].type = T_ARG;
				printf("token[%i].type = %d value = %s\n", i, (int)mini.token[i].type, mini.token[i].value);
				i++;
			}
		}
		else if (mini.token[i].type == T_RLESS && mini.token[i + 1].type == T_ERR)
			mini.token[i + 1].type = T_I_FILE;
		else if ((mini.token[i].type == T_RGREAT || mini.token[i].type == T_DGREAT) && mini.token[i + 1].type == T_ERR)
			mini.token[i + 1].type = T_O_FILE;
		else if ((mini.token[i].type == T_PIPE || mini.token[i].type == T_AND || mini.token[i].type == T_OR) && mini.token[i + 1].type == T_ERR)
			perror("Error ");
		/*else if (mini.token[i].type == T_VAR)
			get_var_name(mini);*/
		printf("token[%i].type = %d value = %s\n", i, (int)mini.token[i].type, mini.token[i].value);
	}
}

int	ft_is_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	return (0);
}

int	get_nb_cmd(t_mini mini)
{
	int	i;
	int	ret;

	i = 0;
	ret = 1;
	while (mini.token[i].type != T_OR && mini.token[i].type != T_AND && mini.cmd_split[i])
	{
		if (mini.token[i].type == T_PIPE)
			ret++;
		i++;
	}
	return (ret);
}

t_mini	isolate_cmd(t_mini mini)
{
	int	i;
	int j;
	int	nb_cmd;

	nb_cmd = get_nb_cmd(mini);
	printf("nb_cmd = %i\n", nb_cmd);
	mini.isolate_cmd = (char **)malloc(sizeof(char *) * (nb_cmd));
	i = 0;
	j = 0;
	while (i < nb_cmd)
	{
		mini.isolate_cmd[i] = "";
		while (mini.token[j].type != T_PIPE && mini.cmd_split[j] && mini.token[j].type != T_OR && mini.token[j].type != T_AND)
		{
			mini.isolate_cmd[i] = ft_strjoin_with_space(mini.isolate_cmd[i], mini.token[j].value);
			j++;
		}
		j++;
		printf("mini.isolate_cmd[%i] = %s\n", i, mini.isolate_cmd[i]);
		i++;
		printf(" j = %i\n", j);
	}
	return (mini);
}

t_mini	get_token_type(t_mini mini)
{
	int	i;

	i = 0;
	while (i < cntwrd(mini.cmd, 32))
	{
		if (ft_strncmp(mini.token[i].value, "<", 1) == 0)
			mini.token[i].type = T_RLESS;
		else if (ft_strncmp(mini.token[i].value, ">", 1) == 0)
			mini.token[i].type = T_RGREAT;
		else if (ft_strncmp(mini.token[i].value, "<<", 2) == 0)
			mini.token[i].type = T_DLESS;
		else if (ft_strncmp(mini.token[i].value, ">>", 2) == 0)
			mini.token[i].type = T_DGREAT;
		else if (ft_strncmp(mini.token[i].value, "|", 1) == 0)
			mini.token[i].type = T_PIPE;
		else if (ft_strncmp(mini.token[i].value, "||", 2) == 0)
			mini.token[i].type = T_OR;
		else if (ft_strncmp(mini.token[i].value, "&&", 2) == 0)
			mini.token[i].type = T_AND;
		else if (ft_is_cmd(mini.token[i].value) == 1)
			mini.token[i].type = T_CMD;
		else if (mini.token[i].value[0] == '$')
			mini.token[i].type = T_VAR;
		else
			mini.token[i].type = T_ERR;
		i++;
	}
	search_for_args(mini);
	mini = isolate_cmd(mini);
	return (mini);
}

void	remove_io_file(t_mini mini, int k)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(mini.isolate_cmd[k]))
	{
		if (mini.isolate_cmd[k][i] == '<' && mini.isolate_cmd[k][i + 1] == '<')
		{
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i + 1] != 32)
			{
				mini.isolate_cmd[k][i] = 32;
				i++;
			}
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i + 1] != 32)
			{
				mini.isolate_cmd[k][i] = 32;
				i++;
			}
			return ;
		}
		else if (mini.isolate_cmd[k][i] == '>' && mini.isolate_cmd[k][i + 1] == '>')
		{
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i + 1] != 32)
			{
				mini.isolate_cmd[k][i] = 32;
				i++;
			}
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i + 1] != 32)
			{
				mini.isolate_cmd[k][i] = 32;
				i++;
			}
			return ;
		}
		else if (mini.isolate_cmd[k][i] == '<')
		{
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i + 1] != 32)
			{
				mini.isolate_cmd[k][i] = 32;
				i++;
			}
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i + 1] != 32)
			{
				mini.isolate_cmd[k][i] = 32;
				i++;
			}
			return ;
		}
		else if (mini.isolate_cmd[k][i] == '>')
		{
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i + 1] != 32)
			{
				mini.isolate_cmd[k][i] = 32;
				i++;
			}
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i + 1] != 32)
			{
				mini.isolate_cmd[k][i] = 32;
				i++;
			}
			return ;
		}
		else
			i++;
	}
}

char	*find_path(char *cmd, char **envp)
{
	char	**split_path;
	char	*o_path;
	char	*part_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	split_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (split_path[i])
	{
		part_path = ft_strjoin(split_path[i], "/");
		o_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(o_path, F_OK | X_OK) == 0)
		{
			return (o_path);
		}
		free(o_path);
		i++;
	}
	free_double(split_path);
	return (cmd);
}

void	ft_execute(char *arg, t_mini mini)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(arg, ' ');
	path = find_path(cmd[0], mini.envp);
	if (execve(path, cmd, mini.envp) == -1)
	{
		free_double(cmd);
		perror("command not found\n");
	}
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
		perror("Error fork bonus \n");
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

int	simple_gnl(char **line, char *limiter)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(BUFSIZ);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i++] = c;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0)
		exit(EXIT_SUCCESS);
	return (r);
}

void	here_doc(char *limiter)
{
	pid_t	pid2;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid2 = fork();
	if (pid2 == 0)
	{
		close(fd[0]);
		line = malloc(BUFSIZ);
		while (simple_gnl(&line, limiter))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			ft_putstr_fd(line, fd[1]);
			free(line);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
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
			mini.infile = open(mini.token[i].value, O_RDONLY, 0777);
		else if (mini.token[i].type == T_O_FILE)
			mini.outfile = open(mini.token[i].value, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		i++;
	}
	dup2(mini.infile, STDIN_FILENO);
	while (i < get_nb_cmd(mini) - 2)
		ft_child_proc(mini.isolate_cmd[i], mini);
	dup2(mini.outfile, STDOUT_FILENO);
	ft_execute(mini.isolate_cmd[get_nb_cmd(mini) - 2], mini);
}

void	parse_cmd(t_mini mini)
{
	remove_io_file(mini, 0);
	remove_io_file(mini, get_nb_cmd(mini) - 1);

	for (int i = 0; i < get_nb_cmd(mini); i++)
		printf("arg[%i] = %s\n", i, mini.isolate_cmd[i]);
	ft_exec_pipex(mini);
}

void	get_lex_of_cmd(t_mini mini)
{
	int		i;

	mini.cmd_split = ft_split(mini.cmd, ' ');
	mini.token = malloc(sizeof(t_token) * cntwrd(mini.cmd, 32));
	i = -1;
	while (++i < cntwrd(mini.cmd, 32))
		mini.token[i].value = mini.cmd_split[i];
	mini = get_token_type(mini);
	parse_cmd(mini);
}

void	init_prompt(char **envp)
{
	t_mini mini;

	mini.envp = envp;
	mini.num_of_pipe = 0;
	while (1)
	{
		mini.cmd = readline(GREEN"MINISHELL DRUCKER A LA RESCOUSSE > "RESET"");
		if (ft_strncmp(mini.cmd, "exit", 4) == 0)
		{
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}
		add_history(mini.cmd);
		get_lex_of_cmd(mini);
		free(mini.cmd);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	
	if (ac == 1)
		init_prompt(envp);
	return (0);
}
