/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:51:12 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:52:02 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_tabjoin(char **s1, char **s2)
{
	char		**dest;
	int			size;
	int			i;

	size = 0;
	i = -1;
	while (s1 && s1[++i])
		size++;
	i = -1;
	while (s2 && s2[++i])
		size++;
	dest = ft_calloc(sizeof(char *), (size + 1));
	size = -1;
	i = -1;
	while (s1 && s1[++i])
		dest[++size] = ft_strdup(s1[i]);
	i = -1;
	while (s2 && s2[++i])
		dest[++size] = ft_strdup(s2[i]);
	return (dest);
}
