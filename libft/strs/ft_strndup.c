/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:50:34 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:52:29 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(char *str, int start, int len)
{
	int		i;
	char	*dest;

	if (!str || start > (int)ft_strlen(str) || len < 0)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_min(len, (int)ft_strlen(str)) + 1));
	if (!(dest))
		return (NULL);
	i = -1;
	while (i < len && str[++i + start])
		dest[i] = str[i + start];
	dest[i] = 0;
	return (dest);
}
