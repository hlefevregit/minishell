/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:51:22 by hulefevr          #+#    #+#             */
/*   Updated: 2024/08/01 15:28:08 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_cd(char **arg, t_mini mini)
{
    if (arg[1] == NULL)
	{
        if (chdir("/home") != 0)
        {
            perror("cd");
            mini.exit_status = EXIT_FAILURE;
        }
    } 
	else if (ft_strcmp(arg[1], "-") == 0)
	{
		if (chdir(find_in_env("OLDPWD", mini.envp)) != 0)
		{
            perror("cd");
            mini.exit_status = EXIT_FAILURE;
        }
	}
	else if (chdir(arg[1]) != 0)
        {
            perror("cd");
            mini.exit_status = EXIT_FAILURE;
        }
	if (mini.exit_status != EXIT_FAILURE)
	mini.exit_status = EXIT_SUCCESS;
}
