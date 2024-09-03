/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:12:31 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/03 16:22:49 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	search_for_args(t_mini mini)
{
	int	i;

	i = -1;
	while (++i < cntwrd(mini.cmd, 32))
	{
		if (mini.token[i].type == T_DLESS && mini.token[i + 1].type == T_ERR)
			mini.token[i + 1].type = T_HEREDOC;
		else if (mini.token[i].type == T_D_QUOTE)
		{
			i++;
			while (mini.token[i].type != T_D_QUOTE && mini.token[i].value != NULL)
			{
				mini.token[i].type = T_ARG;
				i++;
			}
			i++;
		}
		else if (mini.token[i].type == T_S_QUOTE)
		{
			i++;
			while (mini.token[i].type != T_S_QUOTE && !mini.token[i].value)
			{
				mini.token[i].type = T_ARG;
				i++;
			}
			i++;
		}
		else if (mini.token[i].type == T_RLESS && mini.token[i + 1].type == T_ERR)
			mini.token[i + 1].type = T_I_FILE;
		else if (mini.token[i].type == T_RGREAT && mini.token[i + 1].type == T_ERR)
			mini.token[i + 1].type = T_OR_FILE;
		else if ( mini.token[i].type == T_DGREAT && mini.token[i + 1].type == T_ERR)
			mini.token[i + 1].type = T_OD_FILE;
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
	while (mini.cmd_split[i])
	{
		if (mini.token[i].type == T_PIPE)
			ret++;
		i++;
	}
	return (ret);
}

t_mini	get_token_type(t_mini mini)
{
	int	i;

	i = -1;
	while (++i < cntwrd(mini.cmd, 32))
	{
		if (ft_strncmp(mini.token[i].value, "<<", 2) == 0)
			mini.token[i].type = T_DLESS;
		else if (ft_strncmp(mini.token[i].value, ">>", 2) == 0)
			mini.token[i].type = T_DGREAT;
		else if (ft_strncmp(mini.token[i].value, "<", 1) == 0)
			mini.token[i].type = T_RLESS;
		else if (ft_strncmp(mini.token[i].value, ">", 1) == 0)
			mini.token[i].type = T_RGREAT;
		else if (ft_strncmp(mini.token[i].value, "|", 1) == 0)
			mini.token[i].type = T_PIPE;
		else if (ft_strncmp(mini.token[i].value, "'", 1) == 0)
			mini.token[i].type = T_S_QUOTE;
		else if (mini.token[i].value[0] == '"' && !mini.token[i].value[1])
			mini.token[i].type = T_D_QUOTE;
		else if (ft_is_cmd(mini.token[i].value) == 1)
			mini.token[i].type = T_CMD;
		else
			mini.token[i].type = T_ERR;
	}
	return (mini);
}

char	**isolate_cmd(t_mini mini)
{
	int	i;
	int j;
	char **ret;

	ret = (char **)ft_calloc(sizeof(char *), (get_nb_cmd(mini)));
	i = 0;
	j = 0;
	while (i < get_nb_cmd(mini))
	{
		ret[i] = "";
		while (mini.token[j].type != T_PIPE && j < mini.size_cmd)
		{
			// printf("acutal mini.token[%i].type = %d and mini.token[%i].value = %s\n", j, mini.token[j].type, j, mini.token[j].value);
			if (mini.token[j].type == T_ARG || mini.token[j].type == T_CMD
				|| mini.token[j].type == T_S_QUOTE || mini.token[j].type == T_D_QUOTE
				|| mini.token[j].type == T_ERR)
				ret[i] = ft_strjoin_with_space(ret[i], mini.token[j].value);
			j++;
		}
		j++;
		i++;
	}
	return (ret);
}

void	get_lex_of_cmd(t_mini mini)
{
	int		i;

	mini.cmd_split = ft_split_cmd(mini.cmd, mini);
	mini.token = malloc(sizeof(t_token) * (cntwrd(mini.cmd, 32) + cntquotes(mini.cmd) + 2));
	i = -1;
	mini.size_cmd = cntwrd(mini.cmd, 32) + cntquotes(mini.cmd);
	printf("num of token = %i\n", cntwrd(mini.cmd, 32) + cntquotes(mini.cmd));
	while (++i < mini.size_cmd)
	{
		mini.token[i].value = mini.cmd_split[i];
		printf("token[%i] = %s\n", i, mini.token[i].value);
	}
	mini = get_token_type(mini);
	search_for_args(mini);
	mini.isolate_cmd = isolate_cmd(mini);
	if (mini.token)
		free(mini.token);
	for (int j = 0; j < mini.size_cmd; j++)
		printf("mini.cmd_split[%i] = %s\n", j, mini.cmd_split[j]);
	for (int j = 0; j < get_nb_cmd(mini); j++)
		printf("mini.isolate_cmd[%i] = %s\n", j, mini.isolate_cmd[j]);
	ft_exec_pipex(mini);
}
