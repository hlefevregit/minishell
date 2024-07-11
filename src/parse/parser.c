/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugolefevre <hugolefevre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:14:16 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/10 15:48:53 by hugolefevre      ###   ########.fr       */
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
	if (remove_infile(mini, k) == 1)
		return ;
	else if (remove_outfile(mini, k) == 1)
		return ;
	else if (remove_infile_simple(mini, k) == 1)
		return ;
	else if (remove_outfile_simple(mini, k) == 1)
		return ;
}