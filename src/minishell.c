/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:08:54 by hulefevr          #+#    #+#             */
/*   Updated: 2024/06/07 15:27:42 by hulefevr         ###   ########.fr       */
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

void	search_for_args(t_mini mini)
{
	int	i;

	i = -1;
	if (mini.token[0].type == T_ERR)
		perror("Error");
	while (++i < cntwrd(mini.cmd, 32))
	{
		if (mini.token[i].type == T_DLESS && mini.token[i + 1].type == T_ERR)
			mini.token[i + 1].type = T_HEREDOC;
		if (mini.token[i].type == T_CMD)
			while (mini.token[++i].type == T_ERR)
				mini.token[i].type = T_ARG;
		if (mini.token[i].type == T_RLESS && mini.token[i + 1].type == T_ERR)
			mini.token[i + 1].type = T_I_FILE;
		if ((mini.token[i].type == T_RGREAT || mini.token[i].type == T_DGREAT) && mini.token[i + 1].type == T_ERR)
			mini.token[i + 1].type = T_O_FILE;
		if ((mini.token[i].type == T_PIPE || mini.token[i].type == T_AND || mini.token[i].type == T_OR) && mini.token[i + 1].type == T_ERR)
			perror("Error");
	}
}

void	get_token_type(t_mini mini)
{
	int	i;

	i = -1;
	while (++i < cntwrd(mini.cmd, 32))
	{
		if (ft_strncmp(mini.token[i].value, "<", 1) == 0)
			mini.token->type = T_RLESS;
		if (ft_strncmp(mini.token[i].value, ">", 1) == 0)
			mini.token->type = T_RGREAT;
		if (ft_strncmp(mini.token[i].value, "<<", 2) == 0)
			mini.token->type = T_DLESS;
		if (ft_strncmp(mini.token[i].value, ">>", 2) == 0)
			mini.token->type = T_DGREAT;
		if (ft_strncmp(mini.token[i].value, "|", 2) == 0)
			mini.token->type = T_PIPE;
		if (ft_strncmp(mini.token[i].value, "||", 2) == 0)
			mini.token->type = T_OR;
		if (ft_strncmp(mini.token[i].value, "&&", 2) == 0)
			mini.token->type = T_AND;
		if (ft_is_cmd(mini.token[i].value) == 1)
			mini.token[i].type = T_ARG;
		else
			mini.token[i].type = T_ERR;
		printf("token[%i].type = %d value = %s\n", i, (int)mini.token[i].type, mini.token[i].value);
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

void	init_prompt(char **envp)
{
	t_mini mini;

	mini.envp = envp;
	while (1)
	{
		mini.cmd = readline(STDIN_FILENO);
		if (ft_strncmp(mini.cmd, "exit", 4) == 0)
			exit(EXIT_SUCCESS);
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
