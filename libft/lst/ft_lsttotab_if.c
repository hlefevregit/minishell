/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttotab_if.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:47:33 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:54:06 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_lsttotab_if(t_list *lst, int (*cmp)(void *), char *(*conv)(void *))
{
	char	**dest;
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (cmp(tmp->content))
			i++;
		tmp = tmp->next;
	}
	dest = ft_calloc(sizeof(char *), (i + 1));
	if (!(dest))
		return (NULL);
	i = 0;
	while (lst)
	{
		if (cmp(lst->content))
			dest[i++] = conv(lst->content);
		lst = lst->next;
	}
	return (dest);
}
