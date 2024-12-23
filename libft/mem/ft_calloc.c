/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:48:18 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:53:47 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*buffer;
	size_t			i;

	i = 0;
	buffer = (unsigned char *)malloc(count * size);
	if (!(buffer))
		return (0);
	while (i < count * size)
	{
		buffer[i] = 0;
		i++;
	}
	return (buffer);
}
