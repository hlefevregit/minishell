/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bul_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:20:50 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 15:20:50 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

int	plus_in_name(char *env_name)
{
	int	i;

	i = -1;
	while (env_name[++i] && env_name[i] != '=')
		if (env_name[i] == '+')
			return (1);
	return (0);
}

void	remove_plus(char *str)
{
	char	*plus;

	plus = ft_strchr(str, '+');
	if (plus)
		ft_memmove(plus, plus + 1, ft_strlen(plus));
}

int	already_in_env(char *env_name, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->data->env[i] != NULL)
	{
		if (ft_strncmp(cmd->data->env[i], env_name,
				ft_strchr(env_name, '=') - env_name) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_env_name(char *env_name)
{
	int	i;

	i = 1;
	if (!ft_isalpha(env_name[0]) && env_name[0] != '_')
		return (0);
	while (env_name[i] != '=')
	{
		if (env_name[i + 1] == '=' && env_name[i] == '+')
			return (1);
		if (!ft_isalpha(env_name[i]) && !ft_isdigit(env_name[i]))
		{
			if (env_name[i] != ' ' && env_name[i] != '_')
				return (0);
		}
		if (env_name[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}
