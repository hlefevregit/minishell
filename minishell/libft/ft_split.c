/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:08:21 by hlefevre          #+#    #+#             */
/*   Updated: 2022/09/01 15:37:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_length(char *s, char c, int a)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (a)
	{
		if (s[i] == c && s[i + 1] != c)
			a--;
		i++;
	}
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char	*cpyword(char *s, char c, int a)
{
	char	*word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word = malloc(sizeof(char) * word_length(s, c, a) + 1);
	if (!word)
		return (NULL);
	while (s[i] == c)
		i++;
	while (a)
	{
		if (s[i] == c && s[i + 1] != c)
			a--;
		i++;
	}
	while (s[i] && s[i] != c)
	{
		word[j] = s[i];
		j++;
		i++;
	}
	word[j] = 0;
	return (word);
}

static int	word_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		cases;
	char	**tab;

	if (!s)
		return (NULL);
	cases = word_count(s, c);
	tab = malloc(sizeof(char *) * (cases + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < cases)
	{
		tab[i] = cpyword(s, c, i);
		i++;
	}
	tab[i] = 0;
	return (tab);
}