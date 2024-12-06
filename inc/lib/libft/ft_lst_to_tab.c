/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:08:39 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/06 18:08:40 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char	**ft_lst_to_tab(t_list *lst)
{
	char	**dest;
	int		i;

	dest = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!(dest))
		return (NULL);
	i = 0;
	while (lst)
	{
		dest[i] = ft_strdup((char *)lst->content);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
