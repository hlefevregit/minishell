/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:48:14 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:53:52 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	int				i;
	unsigned char	*temp;

	temp = s;
	i = 0;
	while (i < (int)n)
	{
		temp[i] = 0;
		i++;
	}
	s = temp;
}
