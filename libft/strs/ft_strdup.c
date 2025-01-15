/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:49:59 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:52:51 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*dest;

	size = 0;
	while (s1 && s1[size])
		size++;
	dest = malloc((size + 1) * sizeof(char));
	if (!(dest))
		return (NULL);
	size = 0;
	while (s1 && s1[size])
	{
		dest[size] = s1[size];
		size++;
	}
	dest[size] = 0;
	return (&dest[0]);
}
