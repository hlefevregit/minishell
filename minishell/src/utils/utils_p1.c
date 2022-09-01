/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_p1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:39:04 by marvin            #+#    #+#             */
/*   Updated: 2022/09/01 15:39:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*char_toa(char c)
{
	char	*s;

	s = malloc(sizeof(char) * 2);
	s[0] = c;
	s[1] = 0;
	return (s);
}

int	is_empty(char *line)
{
	char	c;

	if (line[0] && (line[0] == '\'' || line[0] == '\"'))
	{
		c = line[0];
		if (line[1] == c && line[1])
		{
			ft_putstr_fd("command not found\n", 1);
			return (1);
		}
	}
	return (0);
}

int	get_quote(char *line);
{
	int		i;
	int		j;
	char	type;

	if (!line)
		return (0);
	i = 0;
	j = 0;
	while (line[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && !j)
		{
			j = 1;
			type = s[i];
		}
		else if (j && s[i] == type)
			j = 0;
	}
	if (j)
		ft_putstr_fd("unclosed quote\n", 1);
	return (j);
}