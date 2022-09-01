/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlefevre <hlefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:42:41 by hlefevre          #+#    #+#             */
/*   Updated: 2021/10/26 13:51:52 by hlefevre         ###   ########.fr       */
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

// 