/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:12:31 by hulefevr          #+#    #+#             */
/*   Updated: 2024/06/10 17:12:58 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
