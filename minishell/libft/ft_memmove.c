/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlefevre <hlefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:18:11 by hlefevre          #+#    #+#             */
/*   Updated: 2021/10/26 14:32:54 by hlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		i;
	char	*s1;
	char	*s2;

	s1 = (char *)dest;
	s2 = (char *)src;
	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1 > s2)
	{
		while (n > 0)
		{
			s1[n - 1] = s2[n - 1];
			n--;
		}
	}
	else
	{
		while (n > 0)
		{
			s1[i] = s2[i];
			i++;
			n--;
		}
	}
	return (dest);
}
