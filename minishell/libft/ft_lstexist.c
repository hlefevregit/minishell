/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstexist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlefevre <hlefevre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 12:14:18 by hlefevre          #+#    #+#             */
/*   Updated: 2021/10/29 12:33:57 by hlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lstexist(t_list *v, char *n)
{
	if (!v)
		return (0);
	while (v)
	{
		if (ft_strcmp(v->name, n) == 0)
			return (v->value);
		v = v->next;
	}
	return (0);
}
