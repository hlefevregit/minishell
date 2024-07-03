/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:14:16 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/03 13:25:41 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_cmd(t_mini mini)
{
	remove_io_file(mini, 0);
	remove_io_file(mini, get_nb_cmd(mini) - 1);

	for (int i = 0; i < get_nb_cmd(mini); i++)
		printf("arg[%i] = %s\n", i, mini.isolate_cmd[i]);
	ft_exec_pipex(mini);
}

void	remove_io_file(t_mini mini, int k)
{
	remove_infile(mini, k);
	remove_outfile(mini, k);
	remove_infile_simple(mini, k);
	remove_outfile_simple(mini, k);
}