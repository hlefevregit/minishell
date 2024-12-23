/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:49:40 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:53:05 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putstr(char *s)
{
	ft_putstr_fd(s, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	while (s && s[++i])
		write(fd, &s[i], 1);
}
