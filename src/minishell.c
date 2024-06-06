/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:08:54 by hulefevr          #+#    #+#             */
/*   Updated: 2024/06/06 18:24:03 by hulefevr         ###   ########.fr       */
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

void	get_token_type(t_mini mini)
{
	int	i;

	i = -1;
	while (++i < cntwrd(mini.cmd, 32))
	{
		if (ft_strncmp(mini.token[i].value, "-", 1) == 0)
			mini.token[i].type = T_FLAG;
		if (ft_strncmp(mini.token[i].value, "<", 1) == 0)
			mini.token->type = T_RLESS;
		if (ft_strncmp(mini.token[i].value, ">", 1) == 0)
			mini.token->type = T_RGREAT;
		if (ft_strncmp(mini.token[i].value, "<<", 2) == 0)
			mini.token->type = T_DLESS;
		if (ft_strncmp(mini.token[i].value, ">>", 2) == 0)
			mini.token->type = T_DGREAT;
		if (ft_strncmp(mini.token[i].value, "|", 1) == 0)
			mini.token->type = T_PIPE;
		if (ft_strncmp(mini.token[i].value, "||", 2) == 0)
			mini.token->type = T_OR;
		if (ft_strncmp(mini.token[i].value, "&&", 2) == 0)
			mini.token->type = T_AND;
		else if (execve(mini.path, mini.cmd_split, mini.envp) != -1)
			mini.token[i].type = T_ARG;
		printf("token[%i].type = %d\n", i, mini.token[i].type);
	}
	// search_for_args_or_cmd(mini);
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

void	init_prompt(char **envp)
{
	t_mini mini;

	mini.envp = envp;
	while (1)
	{
		mini.cmd = readline(STDIN_FILENO);
		mini.path = find_path(mini.cmd, mini.envp);	
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
