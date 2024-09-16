/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:15:48 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/16 19:20:44 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_in_env(char *cmd, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], cmd, ft_strlen(cmd)) == 0
			&& envp[i][ft_strlen(cmd)] == '=')
			return (envp[i] + ft_strlen(cmd) + 1);
		i++;
	}
	return (NULL);
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
			i = -1;
			while (split_path[++i])
				if (split_path[i])
					free(split_path[i]);
			if (split_path)
				free(split_path);
			return (o_path);
		}
		free(o_path);
		i++;
	}
	i = -1;
	while (split_path[++i])
	{
		if (split_path[i])
		{
			free(split_path[i]);
			printf("free split_path[%d]\n", i);
		}
	}
	if (split_path)
		free(split_path);
	return (cmd);
}
