/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:54:34 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/16 16:14:17 by hulefevr         ###   ########.fr       */
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

// int	ft_isspace(int c)
// {
// 	return (c == ' ' || c == '\t' || c == '\n'
// 		|| c == '\v' || c == '\f' || c == '\r');
// }

// char	*ft_strncpy(char *dest, char *src, unsigned int n)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (src[i] != '\0' && i < n)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	while (i < n)
// 	{
// 		dest[i] = '\0';
// 		i++;
// 	}
// 	return (dest);
// }

int count_words_with_quotes(char *str)
{
    int count = 0;
    int in_word = 0;
    
    while (*str)
	{
        if (ft_isspace(*str))
            in_word = 0;
        else if (*str == '\'' || *str == '"')
            count++; // compte chaque quote comme un mot
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
    char *start = *str;
    while (**str && !ft_isspace(**str) && **str != '\'' && **str != '"')
        (*str)++;
    int len = *str - start;
    char *word = malloc(len + 1);
    if (word)
	{
        ft_strncpy(word, start, len);
        word[len] = '\0';
    }
    return (word);
}

char **ft_split_cmd(char *str, t_mini mini)
{
    mini.size_cmd = count_words_with_quotes(str);
    char **result = malloc((mini.size_cmd + 1) * sizeof(char *));
    int index = 0;

    while (*str)
	{
        if (ft_isspace(*str))
            str++; // skip espaces
		else if (*str == '\'' || *str == '"')
		{
            // Isoler quote
            result[index] = malloc(2); // pour le quote + \0
            result[index][0] = *str;
            result[index][1] = '\0';
            index++;
            str++;
        }
		else
		{
            // Copier le mot jusqu'à un espace ou un quote
            result[index] = copy_word(&str);
            index++;
        }
    }
    result[index] = NULL; // fin du tableau
    return (result);
}
