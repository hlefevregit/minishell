/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:54:34 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/23 11:15:17 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cntquotes(char *cmd)
{
	int	s_q;
	int	d_q;
	int	i;

	s_q = 0;
	d_q = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == D_QUOTE)
			d_q++;
		else if (cmd[i] == S_QUOTE)
			s_q++;
		i++;
	}
	return (d_q + s_q);
}

int count_words_with_quotes(char *str)
{
	int count;
	int in_word;
	
	count = 0;
	in_word = 0;
	while (*str)
	{
		if (ft_isspace(*str))
			in_word = 0;
		else if (*str == '\'' || *str == '"')
			count++;
		else if (!in_word)
		{
			count++;
			in_word = 1;
		}
		str++;
	}
	return count;
}

char *copy_word(char **str)
{
	char	*start;
	char	*word;
	int		len;

	start = *str;
	while (**str && !ft_isspace(**str) && **str != '\'' && **str != '"')
		(*str)++;
	len = *str - start;
	word = malloc(len + 1);
	if (word)
	{
		ft_strncpy(word, start, len);
		word[len] = '\0';
	}
	return (word);
}

char **ft_split_cmd(char *str, t_mini mini)
{
	
	char **result;
	int index;

	mini.size_cmd = count_words_with_quotes(str);
	index = 0;
	result = malloc((mini.size_cmd + 1) * sizeof(char *));
	while (*str)
	{
		if (ft_isspace(*str))
			str++;
		else if (*str == '\'' || *str == '"')
		{
			result[index] = malloc(2);
			result[index][0] = *str;
			result[index][1] = '\0';
			index++;
			str++;
		}
		else
		{
			result[index] = copy_word(&str);
			index++;
		}
	}
	result[index] = NULL;
	return (result);
}
