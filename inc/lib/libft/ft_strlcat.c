/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:11:51 by hulefevr          #+#    #+#             */
/*   Updated: 2024/04/22 11:51:59 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	len;

	j = 0;
	len = ft_strlen(dst);
	if (len >= dstsize)
		return (dstsize + ft_strlen(src));
	while (src[j] && dstsize > len + 1)
	{
		dst[len] = src[j];
		j++;
		len++;
	}
	dst[len] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[j]));
}
