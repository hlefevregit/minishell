/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:15:48 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/03 13:18:04 by hulefevr         ###   ########.fr       */
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

char	*find_path(char *cmd, char **envp)
{
	char	**split_path;
	char	*o_path;
	char	*part_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	split_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (split_path[i])
	{
		part_path = ft_strjoin(split_path[i], "/");
		o_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(o_path, F_OK | X_OK) == 0)
		{
			return (o_path);
		}
		free(o_path);
		i++;
	}
	free_double(split_path);
	return (cmd);
}
