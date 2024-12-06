/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:26:39 by hulefevr          #+#    #+#             */
/*   Updated: 2024/04/22 11:27:45 by hulefevr         ###   ########.fr       */
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
