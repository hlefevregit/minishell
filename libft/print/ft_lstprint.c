/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:48:57 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:53:32 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstprint_fd(t_list *lst, int fd)
{
	int		i;

	i = 0;
	while (lst)
	{
		ft_putchar_fd('|', fd);
		ft_putstr_fd((char *)lst->content, fd);
		ft_putstr_fd("|\n", fd);
		lst = lst->next;
		i++;
	}
}

void	ft_lstprint(t_list *lst)
{
	ft_lstprint_fd(lst, 1);
}
