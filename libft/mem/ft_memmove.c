/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:48:45 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:53:37 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*buff;

	buff = malloc(sizeof(unsigned char) * (len + 1));
	if (buff && dst == NULL && src == NULL)
		return (NULL);
	ft_memcpy(buff, src, len);
	ft_memcpy(dst, buff, len);
	free(buff);
	return (dst);
}
