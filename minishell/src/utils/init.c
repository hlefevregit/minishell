/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:06:30 by marvin            #+#    #+#             */
/*   Updated: 2022/09/01 15:06:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_name(char *s)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = ft_strdup("");
	while (s[i] && s[i] != '=')
	{
		tmp = char_toa(s[i]);
		ret = ft_realloc(ret, ft_strlen(ret) + 1);
		ft_strcat(ret, tmp);
		free(tmp);
		i++;
	}
	return (ret);
}

static char	*get_value(char *s)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	i++;
	ret = ft_strdup("");
	while (s[i])
	{
		tmp = char_toa(s[i]);
		ret = ft_realloc(ret, ft_strlen(ret) + 1);
		ft_strcat(ret, tmp);
		free(tmp);
		i++;
	}
	return (ret);
}

t_list	*init_list(char **env)
{
	t_list	*l;
	t_list	*current;
	char	*name;
	char	*value;
	int		i;

	l = NULL;
	i = 0;
	while (env[i])
	{
		name = get_name(env[i]);
		value = get_value(env[i]);
		current = ft_lstnew(name, value);
		ft_lstadd_back(&l, current);
		i++;
	}
	return (l);
}