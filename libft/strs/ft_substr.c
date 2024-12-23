/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:51:04 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:52:09 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			i;

	i = 0;
	if (!s)
		return (0);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	dest = malloc((len + 1) * sizeof(char));
	if (!(dest))
		return (0);
	while (s[i] && i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
