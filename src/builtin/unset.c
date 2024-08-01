/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:10:30 by hulefevr          #+#    #+#             */
/*   Updated: 2024/08/01 17:47:43 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_valid_identifier(const char *str)
{
	if (!str || !(*str))
		return 0;
	if (!(ft_isalpha(*str) || *str == '_'))
		return 0;
	str++;
	while (*str)
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return 0;
		str++;
	}
	return 1;
}

int find_env_var_index(char **env, const char *key)
{
	size_t key_len;
	int i;

	key_len = strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return i;
		i++;
	}
	return -1;
}

void ft_unset(char **arg, t_mini mini)
{
	int		i;
	char	*key;
	int		index;

	if (!arg || !*arg)
	{
		printf("unset: not enough arguments\n");
		g_global.exit_status = 1;
		return;
	}
	i = 1;
	while (arg[i] != NULL)
	{
		key = arg[i];
		if (!is_valid_identifier(key))
		{
			printf("unset: `%s': not a valid identifier\n", key);
			i++;
			continue;
		}
		index = find_env_var_index(mini.envp, key);
		if (index != -1)
		{
			free(mini.envp[index]);
			while (mini.envp[index + 1])
			{
				mini.envp[index] = mini.envp[index + 1];
				index++;
			}
			mini.envp[index] = NULL;
		}
		i++;
	}
}
