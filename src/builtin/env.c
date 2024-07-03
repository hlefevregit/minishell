/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:12:35 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/03 14:13:07 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(char **argv, t_mini mini)
{
	char	**env;

	(void)argv;
	env = mini.envp;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}