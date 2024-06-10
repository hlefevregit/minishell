/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:08:54 by hulefevr          #+#    #+#             */
/*   Updated: 2024/06/10 17:08:21 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../includes/minishell.h"

void	free_double(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

/*void	get_var_name(t_mini mini)
{
	
}*/

void	search_for_args(t_mini mini)
{
	int	i;

	i = -1;
	printf("\n");
	if (mini.token[0].type == T_ERR)
		perror(RED"Error"RESET ": invalid command\n");
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

void	get_token_type(t_mini mini)
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
		printf("token[%i].type = %d value = %s\n", i, (int)mini.token[i].type, mini.token[i].value);
		i++;
	}
	search_for_args(mini);
}

void	get_lex_of_cmd(t_mini mini)
{
	int		i;

	mini.cmd_split = ft_split(mini.cmd, ' ');
	mini.token = malloc(sizeof(t_token) * cntwrd(mini.cmd, 32));
	i = -1;
	while (++i < cntwrd(mini.cmd, 32))
		mini.token[i].value = mini.cmd_split[i];
	get_token_type(mini);
}

char	*find_in_env(char *cmd, char **envp)
{
	char	*ret;
	int		i;
	int		k;

	i = 0;
	while (ft_strnstr(envp[i], cmd , ft_strlen(cmd)) == 0)
		i++;
	k = 0;
	while (envp[i][k] != '\n')
		k++;
	ret = malloc(sizeof(char) * k);
	k = 0;
	while (envp[i][k] != '\n')
	{
		ret[k] = envp[i][k];
		i++;
		k++;
	}
	ret[k] = '\0';
	return (ret);
}

/*void	get_infile(t_mini mini)
{
	int	i;

	i = 0;
	while (mini.token[i].type != T_PIPE)
	{
		if (mini.token[i].type == T_I_FILE)
		{
			mini.infile = open(mini.token[i].value, O_RDONLY, 0777);
			if (mini.infile == -1)
			{
				perror(RED"Error"RESET" : file error\n");
				exit(EXIT_FAILURE);
			}
			dup2(mini.infile, STDIN_FILENO);
		}
	}	
}

int		get_outfile(t_mini mini)
{
	int	i;

	i = 0;
	while (mini.token[i].type && mini.token[i].type != T_AND && mini.token[i].type != T_OR)
	{
		
		if (mini.token[i].type == T_O_FILE)
		{
			mini.outfile = open(mini.token[i].value, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (mini.outfile == -1)
			{
				perror(RED"Error"RESET" : file error\n");
				exit(EXIT_FAILURE);
			}
			return (mini.outfile);
		}
		i++;
	}
	return (mini.outfile);
}

void	ft_execute(t_mini)
{
	
}

void	ft_child_proc(t_mini mini)
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
		mini.status = 0;
		ft_execute(mini);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	parse_cmd(t_mini mini)
{
	int	i;
	int num;

	i = 0;
	num = -1;
	mini.outfile = get_outfile(mini);
	while (mini.token[i].type && mini.token[i].type != T_AND && mini.token[i].type != T_OR)
	{
		if (mini.token[i].type == T_PIPE)
		{
			get_infile(mini);
			num = i;
			ft_child_proc(mini);
		}
		i++;
	}
	dup2(mini.outfile, STDOUT_FILENO);
	if (num != -1)
	{
		mini.status = 2;
		ft_execute(mini);
	}	
}*/

void	init_prompt(char **envp)
{
	t_mini mini;

	mini.envp = envp;
	mini.num_of_pipe = 0;
	while (1)
	{
		mini.cmd = readline(GREEN"MINISHELL DRUCKER A LA RESCOUSSE > "RESET"");
		if (ft_strncmp(mini.cmd, "exit", 4) == 0)
			exit(EXIT_SUCCESS);
		add_history(mini.cmd);
		get_lex_of_cmd(mini);
		//parse_cmd(mini);
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
