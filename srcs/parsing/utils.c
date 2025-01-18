/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:04:02 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/17 20:03:53 by hulefevr         ###   ########.fr       */
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

int	get_token_value(t_lexer *lexer)
{
	t_token	token;

	token = lexer->token;
	if (token == T_OUT_APPEND || token == T_OUT_TRUNCATE
		|| token == T_IN || token == T_HERE_DOC)
		return (0);
	else if (token == T_NONE)
		return (1);
	else
		return (-1);
}

int	is_only_redir(t_list *tokens)
{
	t_list	*tmp;
	int		expected;

	tmp = tokens;
	expected = 0;
	while (tmp)
	{
		if (get_token_value(tmp->content) != expected)
			return (0);
		if (expected == 0)
			expected = 1;
		else
			expected = 0;
		tmp = tmp->next;
	}
	return (1);
}
