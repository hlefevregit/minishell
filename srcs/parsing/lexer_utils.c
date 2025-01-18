/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:02:35 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/17 20:02:13 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	remove_token(t_token token, t_list **node)
{
	if (token == T_PIPE)
	{
		*node = (*node)->next;
		return ;
	}
	*node = (*node)->next;
	((t_lexer *)(*node)->content)->token = ((t_lexer *)(*node)->prev->content)
		->token;
	ft_lstrmone((*node)->prev, &free_lexer);
	*node = (*node)->next;
}

int	token_error(t_list **tokens)
{
	if (!(*tokens)->next)
	{
		ft_printf("minishell: syntax error near unexpected"
			" token `newline'\n");
		return (ft_lstclear(tokens, &free_lexer), 0);
	}
	if (((t_lexer *)(*tokens)->next->content)->token
		!= T_NONE)
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n",
			token_to_strs(((t_lexer *)(*tokens)->next->content)->token));
		return (ft_lstclear(tokens, &free_lexer), 0);
	}
	return (0);
}

int	check_tokens(t_list **tokens)
{
	t_list	*prev;
	t_token	token;

	while (*tokens)
	{
		token = ((t_lexer *)(*tokens)->content)->token;
		if (token == T_NONE
			|| (token == T_PIPE
				&& ((t_lexer *)(*tokens)->next->content)->token != T_NONE))
		{
			prev = (*tokens);
			(*tokens) = (*tokens)->next;
			continue ;
		}
		if (!(*tokens)->next
			|| ((t_lexer *)(*tokens)->next->content)->token != T_NONE)
			return (token_error(tokens));
		remove_token(token, tokens);
	}
	*tokens = prev;
	ft_lstfirst(tokens);
	return (1);
}

int	ft_isquote(char c)
{
	return (c == '"' || c == '\'');
}

void	swap_quote(char *quote, char c)
{
	if (!ft_isquote(c))
		return ;
	if (*quote == 0)
		*quote = c;
	else if (c == *quote)
		*quote = 0;
}
