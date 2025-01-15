/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:19:32 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 15:20:36 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*token_to_strs(t_token token)
{
	if (token == T_PIPE)
		return ("|");
	if (token == T_OUT_TRUNCATE)
		return (">");
	if (token == T_OUT_APPEND)
		return (">>");
	if (token == T_IN)
		return ("<");
	if (token == T_HERE_DOC)
		return ("<<");
	if (token == T_WHITESPACE)
		return ("space");
	return ("arg");
}

t_token	get_token(char *str)
{
	if (!ft_strncmp(str, "|", 1))
		return (T_PIPE);
	if (!ft_strncmp(str, "<<", 2))
		return (T_HERE_DOC);
	if (!ft_strncmp(str, ">>", 2))
		return (T_OUT_APPEND);
	if (!ft_strncmp(str, ">", 1))
		return (T_OUT_TRUNCATE);
	if (!ft_strncmp(str, "<", 1))
		return (T_IN);
	if (ft_iswhitespace(*str))
		return (T_WHITESPACE);
	return (T_NONE);
}

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

int	skip_quotes(char *input)
{
	char	quote;
	int		i;

	i = 0;
	quote = *input;
	input++;
	while (quote && input[i])
	{
		swap_quote(&quote, input[i]);
		i++;
	}
	return (i);
}

t_lexer	*new_token(char *str, int len, t_token token)
{
	t_lexer	*dest;

	dest = ft_calloc(1, sizeof(t_lexer));
	if (len == -1)
		dest->str = ft_strdup(str);
	else if (len)
		dest->str = ft_substr(str, 0, len);
	dest->token = token;
	return (dest);
}

char	*add_token(t_list **dest, t_token token, char *input, int *i)
{
	if (*i != 0)
		ft_lstadd_back(dest, ft_lstnew(new_token(input, *i, T_NONE)));
	ft_lstadd_back(dest, ft_lstnew(new_token(token_to_strs(token), -1, token)));
	input += ft_strlen(token_to_strs(token)) + *i;
	*i = 0;
	return (input);
}

char	*add_whitespace(t_list **dest, t_token token, char *input, int *i)
{
	if (*i != 0)
		ft_lstadd_back(dest, ft_lstnew(new_token(input, *i, T_NONE)));
	while (token == T_WHITESPACE)
		token = get_token(input + ++(*i));
	input = input + *i;
	*i = 0;
	return (input);
}

t_list	*input_lexer(char *input)
{
	t_list	*dest;
	t_token	found_token;
	int		i;

	i = 0;
	dest = NULL;
	while (input && input[i])
	{
		if (ft_isquote(input[i]))
		{
			i += skip_quotes(input + i) + 1;
			continue ;
		}
		found_token = get_token(input + i);
		if (found_token == T_NONE)
			i++;
		else if (found_token != T_WHITESPACE)
			input = add_token(&dest, found_token, input, &i);
		else if (found_token == T_WHITESPACE)
			input = add_whitespace(&dest, found_token, input, &i);
	}
	if (i != 0)
		ft_lstadd_back(&dest, ft_lstnew(new_token(input, i, T_NONE)));
	return (dest);
}
