/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:21:03 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 15:21:04 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

int	check_echo_opt(char *option)
{
	int	i;

	if (option[0] != '-' || option[1] != 'n')
		return (0);
	i = 1;
	while (option[++i])
		if (option[i] != 'n')
			return (0);
	return (1);
}

int	print_env(t_cmd *cmd, char *name)
{
	int	i;

	i = 0;
	if (name[0] != '$')
		return (0);
	name++;
	while (cmd->data->env[i])
	{
		if (ft_strncmp(cmd->data->env[i], name,
				ft_strchr(cmd->data->env[i], '=') - cmd->data->env[i]) == 0)
		{
			printf("%s", ft_strchr(cmd->data->env[i], '=') + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_opt;

	i = 1;
	if (cmd->args[i] == NULL)
	{
		ft_putstr("\n");
		return ;
	}
	n_opt = check_echo_opt(cmd->args[i]);
	if (n_opt == 1 && cmd->args[i + 1] == NULL)
		return ;
	while (check_echo_opt(cmd->args[i]))
		i++;
	while (cmd->args[i] != NULL)
	{
		if (!print_env(cmd, cmd->args[i]))
			ft_putstr(cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
			ft_putstr(" ");
		i++;
	}
	if (n_opt == 0)
		ft_putstr("\n");
	cmd->data->last_error = 0;
}
