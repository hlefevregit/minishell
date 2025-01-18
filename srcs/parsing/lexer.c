/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:19:32 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/17 18:29:48 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
