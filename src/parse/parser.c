/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugolefevre <hugolefevre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:14:16 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/26 16:56:29 by hugolefevre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_cmd(t_mini mini)
{
	for (int i = 0; i < get_nb_cmd(mini); i++)
		printf("arg[%i] = %s\n", i, mini.isolate_cmd[i]);
	ft_exec_pipex(mini);
}
