/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:51:08 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:52:08 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_tabcpy(char **strs)
{
	int			i;
	char		**dest;

	dest = ft_calloc(sizeof(char *), (ft_tablen(strs) + 1));
	i = -1;
	while (strs && strs[++i])
		dest[i] = ft_strdup(strs[i]);
	return (dest);
}
