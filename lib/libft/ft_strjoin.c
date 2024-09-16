/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:03:42 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/16 17:35:15 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// char	*ft_strjoin_with_space(char *s1, char *s2)
// {
// 	char			*dest;
// 	unsigned int	i;
// 	unsigned int	j;
// 	size_t			size;

// 	j = 0;
// 	i = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	size = ft_strlen(s1) + ft_strlen(s2);
// 	dest = ft_calloc(sizeof(char), (size + 2));
// 	if (!dest)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		dest[i] = s1[i];
// 		i++;
// 	}
// 	dest[i] = 32;
// 	i++;
// 	while (s2[j])
// 	{
// 		dest[i + j] = s2[j];
// 		j++;
// 	}
// 	return (dest);
// }
size_t total_length(char *s1, char *s2)
{
    size_t len = 0;
    if (s1)
        len += ft_strlen(s1);
    if (s2)
        len += ft_strlen(s2);
    return (len);
}

// Fonction qui joint les deux chaînes avec un espace entre elles
char *ft_strjoin_with_space(char *s1, char *s2)
{
	int		i;
	int		j;
	char 	*result;
	size_t	len;
    
	len = total_length(s1, s2);
    result = malloc(len + 1);
    if (!result) 
        return (NULL);
    result[0] = '\0';
    i = 0;
    while (s1 && s1[i])
	{
        result[i] = s1[i];
		i++;
	}
    if (s1 && s2)
	{
        result[i] = ' ';
		i++;
	}
    j = -1;
    while (s2 && s2[++j])
	{
        result[i] = s2[j];
        i++;
    }
    result[i] = '\0';
    return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dest;
	unsigned int	i;
	unsigned int	j;
	size_t			size;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	dest = ft_calloc(sizeof(char), (size + 1));
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
