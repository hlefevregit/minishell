/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:50:12 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:52:43 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*dest;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dest = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!(dest))
		return (0);
	ft_strlcpy(dest, s1, len_s1 + 1);
	ft_strlcpy(dest + len_s1, s2, len_s2 + 1);
	dest[len_s1 + len_s2] = 0;
	return (dest);
}
