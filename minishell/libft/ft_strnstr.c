/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlefevre <hlefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:21:44 by hlefevre          #+#    #+#             */
/*   Updated: 2021/10/26 12:24:43 by hlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *haystack, char const *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (haystack == needle || ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[i] && len > i)
	{
		j = 0;
		while (haystack[i + j] && needle[j]
			&& haystack[i + j] == needle[j] && i + j < len)
		{
			j++;
		}
		if (j == ft_strlen(needle))
		{
			return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
