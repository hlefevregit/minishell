/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlefevre <hlefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 09:29:31 by hlefevre          #+#    #+#             */
/*   Updated: 2021/10/28 18:15:33 by hlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*str;
	size_t	size;

	size = len;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) <= len)
		size = ft_strlen(s);
	str = malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	i = 0;
	while (len > 0 && s[start] && size != 0)
	{
		str[i] = s[start];
		i++;
		start++;
		len--;
	}
	str[i] = '\0';
	return (str);
}
