/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:50:47 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:52:20 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_strs_to_tab(int n, ...)
{
	va_list			ap;
	int				i;
	char			**dest;

	va_start(ap, n);
	dest = (char **)malloc(sizeof(char *) * (n + 1));
	if (!(dest))
		return (NULL);
	i = -1;
	while (++i < n)
		dest[i] = ft_strdup(va_arg(ap, char *));
	dest[i] = NULL;
	va_end(ap);
	return (dest);
}
