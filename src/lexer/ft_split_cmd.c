/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:54:34 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/02 15:28:29 by hulefevr         ###   ########.fr       */
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

char	*quote_dup(char c)
{
	char	*ret;

	ret = malloc(sizeof(char) * (2));
	if (c == S_QUOTE)
		ret[0] = '\'';
	else if (c == D_QUOTE)
		ret[0] = '"';
	ret[1] = '\0';
	return (ret);
}

static int	split_words(char **result, char *s, char c, int word)
{
	int		start_cur;
	int		end_cur;

	end_cur = 0;
	start_cur = 0;
	while (s[end_cur])
	{
		if (s[end_cur] == c || s[end_cur] == 0)
			start_cur = end_cur + 1;
		if (s[end_cur] != c && (s[end_cur + 1] == c || s[end_cur + 1] == 0))
		{
			result[word] = malloc(sizeof(char) * (end_cur - start_cur + 2));
			if (!result[word])
			{
				while (word++)
					free(result[word]);
				return (0);
			}
			ft_strlcpy(result[word], (s + start_cur), end_cur - start_cur + 2);
			word++;
		}
		if (s[end_cur] == S_QUOTE || s[end_cur] == D_QUOTE)
		{
			result[word] = quote_dup(s[end_cur]);
			word++;
			end_cur++;
		}
		end_cur++;
	}
	return (1);
}

char	**remove_s_d_quotes(char **s, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		if (ft_strlen (s[i]) == 1)
			i++;
		else
		{
			while (s[i][j])
			{	
				if (s[i][j] == S_QUOTE)
					s[i][j] = 2;
				else if (s[i][j] == D_QUOTE)
					s[i][j] = 2;
				j++;
			}
			i++;
		}
	}
	return (s);
}

char	**ft_split_cmd(char *s, t_mini mini)
{
	char	**ret;

	mini.size_cmd = cntwrd(s, 32) + cntquotes(s);
	ret = ft_calloc(sizeof(char *), mini.size_cmd);
	if (!ret)
		return (NULL);
	if (!split_words(ret, s, 32, 0))
		return (NULL);
	ret = remove_s_d_quotes(ret, mini.size_cmd);
	// for (int r = 0; r < mini.size_cmd; r++)
	// 	printf("split[%i] = %s\n", r, ret[r]);
	return (ret);
}
