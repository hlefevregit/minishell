/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:32:22 by marvin            #+#    #+#             */
/*   Updated: 2022/09/01 15:32:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *s, int size)
{
	char	*ret;
	int		current;

	if (!s)
		return (malloc(size));
	current = ft_strlen(s);
	if (size <= current)
		return (s);
	ret = malloc(size + 1);
	ret = ft_memcpy(ret, s, current);
	free(s);
	return (ret);
}