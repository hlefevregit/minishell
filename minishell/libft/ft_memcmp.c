/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlefevre <hlefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:55:46 by hlefevre          #+#    #+#             */
/*   Updated: 2021/10/22 12:44:59 by hlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int		i;
	unsigned char		*d1;
	unsigned char		*d2;

	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	i = 0;
	while (n > 0)
	{
		if (d1[i] != d2[i])
		{
			return (d1[i] - d2[i]);
		}
		i++;
		n--;
	}
	return (0);
}

// x