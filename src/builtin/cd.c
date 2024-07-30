/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugolefevre <hugolefevre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:51:22 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/28 13:27:32 by hugolefevre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_cd(char **arg, t_mini mini)
{
	char	*home;

    if (arg[1] == NULL)
	{
        home = find_in_env("HOME", mini.envp);
        if (home == NULL)
		{
            printf("cd: Impossible de trouver le répertoire home.\n");
            mini.exit_status = EXIT_FAILURE;
            return ;
        }
        if (chdir(home) != 0)
            perror("cd");
    } 
	else
        if (chdir(arg[1]) != 0)
            perror("cd");
}
