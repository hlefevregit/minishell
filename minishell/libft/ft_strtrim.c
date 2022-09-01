/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlefevre <hlefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:42:26 by hlefevre          #+#    #+#             */
/*   Updated: 2021/10/28 18:38:35 by hlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*d;
	size_t	l;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	l = ft_strlen(s1);
	while (ft_strchr(set, s1[l]) && l) 
	{
		l--;
	}
	d = ft_substr((char *)s1, 0, l + 1);
	return (d);
}
 