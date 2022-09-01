/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlefevre <hlefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:11:39 by hlefevre          #+#    #+#             */
/*   Updated: 2021/10/24 13:06:51 by hlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*g;

	i = 0;
	g = ft_strdup(s);
	if (!g || !f || !s)
	{
		return (NULL);
	}
	while (g[i])
	{
		g[i] = f(i, g[i]);
		i++;
	}
	return (g);
}
