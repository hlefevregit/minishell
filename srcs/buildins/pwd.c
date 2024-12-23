/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:22:06 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 15:22:07 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = get_var_from_env(cmd->data->env, "PWD");
	printf("%s\n", pwd + 4);
}
