/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_to.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:50:08 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:52:46 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_strjoin_to(char **dest, char *s2)
{
	char		*temp;

	temp = *dest;
	*dest = ft_strjoin(*dest, s2);
	free(temp);
}
