/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:48:39 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:53:38 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*bufferdst;
	unsigned char	*buffersrc;

	if (dst == NULL && src == NULL)
		return (NULL);
	bufferdst = (unsigned char *)dst;
	buffersrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		bufferdst[i] = buffersrc[i];
		i++;
	}
	dst = bufferdst;
	return (dst);
}
