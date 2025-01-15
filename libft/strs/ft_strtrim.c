/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:50:51 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:52:17 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		i;
	int		start;
	char	*dest;

	i = 0;
	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (s1[i] == 0)
		return (ft_strdup(""));
	len -= i;
	start = i;
	i = ft_strlen(s1) - 1;
	while (i > start && ft_strchr(set, s1[i]))
	{
		i--;
		len--;
	}
	dest = ft_substr(s1, start, len);
	return (dest);
}
