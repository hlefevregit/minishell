/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:34:32 by hulefevr          #+#    #+#             */
/*   Updated: 2024/04/22 11:32:25 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *big, char const *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (big == little || ft_strlen(little) == 0)
		return ((char *)big);
	while (big[i] && len > i)
	{
		j = 0;
		while (big[i + j] && little[j]
			&& big[i + j] == little[j] && i + j < len)
		{
			j++;
		}
		if (j == ft_strlen(little))
		{
			return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
