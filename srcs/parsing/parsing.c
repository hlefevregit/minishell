/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:19:19 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/17 20:04:15 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_quotes(void *content)
{
	t_lexer	*token;
	int		i;
	char	quote;

	quote = 0;
	token = content;
	if (token->token != T_NONE)
		return ;
	i = 0;
	while (token->str[i])
	{
		if (ft_isquote(token->str[i]) && (!quote || quote == token->str[i]))
		{
			swap_quote(&quote, token->str[i]);
			ft_memmove(token->str + i, token->str + i + 1, ft_strlen(token->str
					+ i + 1) + 1);
			continue ;
		}
		i++;
	}
}

void	create_cmd(t_data *data, t_list *tokens)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	expand_env(data, tokens);
	ft_lstiter(tokens, &remove_quotes);
	cmd->args = ft_lsttotab_if(tokens, &is_arg, &lst_conv);
	ft_lstrm_if(&tokens, &is_arg, &free_lexer);
	cmd->out = tokens;
	cmd->name = cmd->args[0];
	cmd->data = data;
	ft_lstadd_back(&data->cmds, ft_lstnew(cmd));
}

int	is_only_space(char *input)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (input[i] == ' ')
		i++;
	j = 0;
	while (input[j] == '|')
		j++;
	if (j == ft_strlen(input) || i == ft_strlen(input))
		return (1);
	return (0);
}

int	is_redir(t_token token)
{
	if (token == T_IN || token == T_OUT_APPEND
		|| token == T_OUT_TRUNCATE || token == T_HERE_DOC)
		return (1);
	return (0);
}

int	parse_input(t_data *data, char *input)
{
	t_list	*tokens;
	t_list	**splitted_tokens;
	int		i;

	if (!input[0])
		return (1);
	if (is_only_space(input))
		return (1);
	tokens = input_lexer(input);
	if (is_only_redir(tokens))
	{
		ft_lstclear(&tokens, &free_lexer);
		return (1);
	}
	if (check_tokens(&tokens) == 0)
		return (0);
	splitted_tokens = ft_lstsplit(tokens, &is_pipe, &free_lexer);
	i = 0;
	while (splitted_tokens[i])
	{
		create_cmd(data, splitted_tokens[i]);
		i++;
	}
	free(splitted_tokens);
	return (1);
}
