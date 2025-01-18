/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:14:06 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/17 20:01:51 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_env_variable(char *str, t_data *data)
{
	int		i;
	char	*tmp;
	char	*dest;

	i = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	tmp = ft_substr(str, 1, i - 1);
	if (!tmp)
		return (NULL);
	dest = get_var_from_env(data->env, tmp);
	free(tmp);
	if (!dest)
		return (NULL);
	return (dest + i);
}

static void	ft_str_replace(char **s1, int start, int len, char *s2)
{
	char	*tmp;

	tmp = ft_substr(*s1, 0, start);
	ft_strjoin_to(&tmp, s2);
	ft_strjoin_to(&tmp, *s1 + start + len);
	free(*s1);
	*s1 = tmp;
}

static void	handle_var(t_lexer *token, t_data *data, int i)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	if (ft_strncmp(token->str + i, "$?", 2) == 0)
	{
		tmp = ft_itoa(g_pid);
		ft_str_replace(&token->str, i, 2, tmp);
		free(tmp);
	}
	else
	{
		len = 1;
		while (token->str[i + len] && (ft_isalnum(token->str[i + len])
				|| token->str[i] == '_'))
			len++;
		ft_str_replace(&token->str, i, len, find_env_variable(token->str + i,
				data));
	}
}

static void	replace_env(t_lexer *token, t_data *data)
{
	int		i;
	char	quote;

	if (token->token != T_NONE)
		return ;
	quote = 0;
	i = 0;
	while (token->str[i])
	{
		if (ft_isquote(token->str[i]))
			swap_quote(&quote, token->str[i]);
		else if (token->str[i] == '$' && quote != '\'' && token->str[i + 1])
		{
			handle_var(token, data, i);
			i--;
		}
		i++;
	}
}

void	expand_env(t_data *data, t_list *tokens)
{
	while (tokens)
	{
		replace_env(tokens->content, data);
		tokens = tokens->next;
	}
}
