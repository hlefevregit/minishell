/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:49:03 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:53:31 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_print_tab(char **strs)
{
	ft_print_tab_fd(strs, 1);
}

void	ft_print_tab_fd(char **strs, int fd)
{
	int			i;

	i = -1;
	while (strs && strs[++i])
	{
		ft_putstr_fd(strs[i], fd);
		ft_putchar_fd('\n', fd);
	}
}
