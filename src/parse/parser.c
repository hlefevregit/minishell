/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:14:16 by hulefevr          #+#    #+#             */
/*   Updated: 2024/06/12 13:59:12 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
void	remove_io_file(t_mini mini, int k)
{
	int	i;

	i = 0;	
	while (mini.isolate_cmd[k][i])
	{
		if (mini.isolate_cmd[k][i] == '<' && mini.isolate_cmd[k][i + 1] == '<')
		{
			while (mini.isolate_cmd[k][i + 3] != '\0' && mini.isolate_cmd[k][i + 3] != 32)
			{
				mini.isolate_cmd[k][i + 3] = 32;
				i++;
			}
		}
		else if (mini.isolate_cmd[k][i] == '>' && mini.isolate_cmd[k][i + 1] == '>')
		{
			while (mini.isolate_cmd[k][i + 3] != '\0' && mini.isolate_cmd[k][i + 3] != 32)
			{
				mini.isolate_cmd[k][i + 3] = 32;
				i++;
			}
		}
		else if (mini.isolate_cmd[k][i] == '<')
		{
			while (mini.isolate_cmd[k][i + 2] != '\0' && mini.isolate_cmd[k][i + 2] != 32)
			{
				mini.isolate_cmd[k][i + 2] = 32;
				i++;
			}
		}
		else if (mini.isolate_cmd[k][i] == '>')
		{
			while (mini.isolate_cmd[k][i + 2] != '\0' && mini.isolate_cmd[k][i + 2] != 32)
			{
				mini.isolate_cmd[k][i + 2] = 32;
				i++;
			}
		}
		i++;
	}
}

void	parse_cmd(t_mini mini)
{
	remove_io_file(mini, 0);
	remove_io_file(mini, get_nb_cmd - 1);

	for (int i = 0; i < get_nb_cmd; i++)
		printf("arg[%i] = %s\n", i, mini.isolate_cmd[i]);
}
*/