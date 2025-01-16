/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabrmi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:51:20 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/16 17:21:18 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_tabrmi(char **strs, int index)
{
	char	**new_strs;
	int		i;
	int		j;
	int		size;

	size = ft_tablen(strs);
	new_strs = ft_calloc(size, sizeof(char *));
	if (!(new_strs) || index < 0 || index > size)
		return (NULL);
	i = -1;
	j = 0;
	while (strs[++i])
	{
		if (i == index)
			j++;
		else
			new_strs[i - j] = ft_strdup(strs[i]);
	}
	new_strs[i - j] = NULL;
	return (new_strs);
}
