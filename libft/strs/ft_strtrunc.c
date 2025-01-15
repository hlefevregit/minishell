/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:50:56 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:52:13 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strtrunc(char **line, int n)
{
	int		size;
	char	*temp;

	if (!line || !(*line))
		return (0);
	size = ft_strlen(*line);
	if (n > size)
		return (0);
	(*line)[size - n] = 0;
	temp = ft_strdup(*line);
	free(*line);
	*line = temp;
	return (1);
}
