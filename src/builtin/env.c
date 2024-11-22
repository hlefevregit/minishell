/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:12:35 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/26 16:20:44 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	printf_sorted_env2(char **envp)
{
	int		i;
	int		sorted;
	char	*tmp;
	char	**sorted_env;
	
	i = 0;
	while (envp[i])
		i++;
	sorted_env = malloc(sizeof(char *) * (i + 1));
	if (!sorted_env)
		exit(EXIT_FAILURE);
	i = 0;
	while (envp[i])
	{
		sorted_env[i] = envp[i];
		i++;
	}
	sorted_env[i] = NULL;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (sorted_env[i + 1])
		{
			if (ft_strcmp(sorted_env[i], sorted_env[i + 1]) > 0)
			{
				tmp = sorted_env[i];
				sorted_env[i] = sorted_env[i + 1];
				sorted_env[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
	i = 0;
	while (sorted_env[i])
	{
		printf("%s\n", sorted_env[i]);
		i++;
	}
	free(sorted_env);	
}

void	ft_env(char **argv, t_mini mini)
{
	char	**env;

	(void)argv;
	env = mini.envp;
	printf_sorted_env2(env);
}