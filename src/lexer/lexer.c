/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:12:31 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/26 15:24:43 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	search_for_args2(t_mini mini, int i)
{
	if (mini.token[i].type == T_D_QUOTE)
	{
		i++;
		while (mini.token[i].type != T_D_QUOTE && mini.token[i].value != NULL)
		{
			if (mini.token[i].type != T_VAR)
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
	return (i);
}

void	search_for_args(t_mini mini)
{
	int	i;

	i = -1;
	while (++i < cntwrd(mini.cmd, 32))
	{
		if (mini.token[i].type == T_DLESS && mini.token[i + 1].type == T_ERR)
			mini.token[i + 1].type = T_HEREDOC;
		else if (mini.token[i].type == T_D_QUOTE || mini.token[i].type == T_S_QUOTE)
			i = search_for_args2(mini, i);
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
	while (mini.token[i].value != NULL)
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
		else if (mini.token[i].value[0] == '$')
			mini.token[i].type = T_VAR;
		else if (mini.token[i].value[0] == '"' && !mini.token[i].value[1])
			mini.token[i].type = T_D_QUOTE;
		else if (ft_is_cmd(mini.token[i].value) == 1)
			mini.token[i].type = T_CMD;
		else
			mini.token[i].type = T_ERR;
	}
	return (mini);
}
char	**isolate_cmd1(t_mini mini)
{
	int		i;
	int		j;
	char	**ret;
	char	*tmp;

	ret = (char **)ft_calloc(get_nb_cmd(mini) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < get_nb_cmd(mini))
	{
		ret[i] = ft_strdup("");
		if (!ret[i])
			return (NULL);
		while (j < mini.size_cmd && mini.token[j].type != T_PIPE)
		{
			tmp = ft_strjoin_with_space(ret[i], mini.token[j].value);
			free(ret[i]);
			ret[i] = tmp;
			j++;
		}
		j++;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	**isolate_cmd(t_mini mini)
{
	int		i;
	int		j;
	char	**ret;
	char	*tmp;

	ret = (char **)ft_calloc(get_nb_cmd(mini) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < get_nb_cmd(mini))
	{
		ret[i] = ft_strdup("");
		if (!ret[i])
			return (NULL);
		while (j < mini.size_cmd && mini.token[j].type != T_PIPE)
		{
			if (mini.token[j].type == T_VAR)
			{
				if (mini.token[j].value[1] != '?')
				{
					tmp = ft_strjoin_with_space(ret[i], \
					find_in_env(mini.token[j].value, mini.envp));
				}
				else
				{
					tmp = ft_strjoin_with_space(ret[i], mini.token[j].value);
				}
			}
			else
				tmp = ft_strjoin_with_space(ret[i], mini.token[j].value);
			free(ret[i]);
			ret[i] = tmp;
			j++;
		}
		j++;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	get_lex_of_cmd(t_mini mini)
{
	int		i;

	mini.cmd_split = ft_split_cmd(mini.cmd, mini);
	if (!mini.cmd_split)
		return (-1);
	mini.token = malloc(sizeof(t_token) * (cntwrd(mini.cmd, 32) + cntquotes(mini.cmd) + 2));
	i = -1;
	mini.size_cmd = cntwrd(mini.cmd, 32) + cntquotes(mini.cmd);
	while (++i < mini.size_cmd)
		mini.token[i].value = mini.cmd_split[i];
	mini = get_token_type(mini);
	search_for_args(mini);
	mini.num_cmd = get_nb_cmd(mini);
	mini.isolate_cmd = isolate_cmd(mini);
	mini.isolate_cmd2 = isolate_cmd1(mini);
	if (mini.token)
		free(mini.token);
	if (ft_exec_pipex(mini))
		return (-1);
	printf("LEX\n");
	free_struct(mini);
	return (0);
}
