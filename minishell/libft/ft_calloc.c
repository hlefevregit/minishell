/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlefevre <hlefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:31:45 by hlefevre          #+#    #+#             */
/*   Updated: 2021/10/28 11:55:57 by hlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*s;

	i = 0;
	s = malloc(size * count);
	if (!s)
	{
		return (NULL);
	}
	ft_memset(s, 0, count * size);
	return (s);
}
