/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:08:08 by hulefevr          #+#    #+#             */
/*   Updated: 2024/11/12 18:23:21 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*get_cmd_data(t_cmd *cmd, t_token *token, char **env)
{
	while (token)
	{
		if (token->type == T_RGREAT && token->next)
			cmd->out = open(token->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (token->type == T_DGREAT && token->next)
			cmd->out = open(token->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (token->type == T_I_FILE && token->next)
			cmd->in = open(token->next->value, O_RDONLY);
		else if (token->type == T_DLESS && token->next)
		{
			cmd->heredoc = 1;
			cmd->limiter = token->next->value;
		}
		else if (token->type == T_PIPE)
			cmd->pipe = 1;
		else if (token->type == T_VAR)
			cmd->cmd = find_in_env(token->value, env);
		token = token->next;
	}
	return (cmd);
}

t_data	get_lex(t_shell *shell)
{
	t_data	data;
	int		i;

	i = 0;
	data = init_data(&data);
	while (shell->line[i] && shell->line[i] != '|')
	{
		if (shell->line[i] == '\'' || shell->line[i] == '\"')
		{
			if (shell->line[i] == '\'')
				while (shell->line[i] != '\'')
					i++;
			else
				while (shell->line[i] != '\"')
					i++;
		}
		else if (shell->line[i++] == '|')
		{
			data.cmd->cmd = ft_substr(shell->line, 0, i);
			data.cmd->args = ft_split(data.cmd->cmd, ' ');
			data.cmd->next = malloc(sizeof(t_cmd));
			data.cmd = data.cmd->next;
			data.num_cmd++;
		}
		i++;
	}
	data.cmd->cmd = ft_substr(shell->line, 0, i);
	data.cmd->args = ft_split(data.cmd->cmd, ' ');
	i = 0;
	while (i != data.num_cmd)
	{
		data.token = get_token(data.cmd->args);
		data.cmd = get_cmd_data(data.cmd, data.token, shell->envp);
		data.cmd = data.cmd->next;
		data.token = data.token->next;
		i++;
	}
	return (data);
}

t_token		*get_token(char **args)
{
	t_token	*token;
	int		i;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	s_quote = false;
	d_quote = false;
	token = malloc(sizeof(t_token));
	while (args[i])
	{
		if (s_quote == false && d_quote == false)
		{
			if (args[i][0] == '>')
			{
				if (args[i][1] == '>')
					token->type = T_DGREAT;
				else
					token->type = T_RGREAT;
			}
			else if (args[i][0] == '<')
			{
				if (args[i][1] == '<')
					token->type = T_DLESS;
				else
					token->type = T_I_FILE;
			}
			else if (args[i][0] == '|')
				token->type = T_PIPE;
			else if (args[i][0] == '$')
				token->type = T_VAR;
			else if (args[i][0] == '\'')
			{
				token->type = T_S_QUOTE;
				s_quote = true;
			}
			else if (args[i][0] == '\"')
			{
				token->type = T_D_QUOTE;
				d_quote = true;
			}
			else
				token->type = T_ERR;
		}
		else if (s_quote == false && d_quote == true)
		{
			if (args[i][0] == '$')
				token->type = T_VAR;
		}
		else
		{
			token->type = T_ARG;
		}
		token->value = args[i];
		token->next = malloc(sizeof(t_token));
		token = token->next;
		i++;
	}
	return (token);
}