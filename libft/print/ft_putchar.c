/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:49:26 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:53:11 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
