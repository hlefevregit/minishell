/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:15:48 by hulefevr          #+#    #+#             */
/*   Updated: 2024/06/10 17:16:09 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_in_env(char *cmd, char **envp)
{
	char	*ret;
	int		i;
	int		k;

	i = 0;
	while (ft_strnstr(envp[i], cmd , ft_strlen(cmd)) == 0)
		i++;
	k = 0;
	while (envp[i][k] != '\n')
		k++;
	ret = malloc(sizeof(char) * k);
	k = 0;
	while (envp[i][k] != '\n')
	{
		ret[k] = envp[i][k];
		i++;
		k++;
	}
	ret[k] = '\0';
	return (ret);
}
