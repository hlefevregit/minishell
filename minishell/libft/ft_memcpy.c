/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlefevre <hlefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:48:22 by hlefevre          #+#    #+#             */
/*   Updated: 2021/10/26 13:55:27 by hlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int		i;
	char	*s1;
	char	*s2;

	s1 = (char *)dest;
	s2 = (char *)src;
	i = 0;
	if (!s1 && !s2)
	{
		return (NULL);
	}
	while (n > 0)
	{
		s1[i] = s2[i];
		i++;
		n--;
	}
	return (dest);
}
