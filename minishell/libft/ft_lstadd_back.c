/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 12:08:21 by hlefevre          #+#    #+#             */
/*   Updated: 2022/09/01 15:19:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **v, t_list *new)
{
	t_list	*elt;

	if (!v)
		return ;
	if (*v)
	{
		elt = ft_varlast(*v);
		elt->next = new;
	}
	else
		*v = new;
}
