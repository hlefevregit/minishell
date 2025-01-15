/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:50:17 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:52:41 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		size;

	size = ft_strlen(dst);
	if (size > dstsize)
		return (dstsize + ft_strlen(src));
	return (ft_strlcpy(dst + size, src, dstsize - size) + size);
}
