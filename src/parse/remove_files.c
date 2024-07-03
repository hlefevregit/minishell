/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:24:17 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/03 13:28:11 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_infile(t_mini mini, int k)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(mini.isolate_cmd[k]))
	{
		if (mini.isolate_cmd[k][i] == '<' && mini.isolate_cmd[k][i + 1] == '<')
		{
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i] == '<')
			{
				mini.isolate_cmd[k][i] = 0;
				i++;
			}
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i] != 32)
			{
				mini.isolate_cmd[k][i] = 0;
				i++;
			}
			return ;
		}
		else
			i++;
	}
}

void	remove_infile_simple(t_mini mini, int k)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(mini.isolate_cmd[k]))
	{
		if (mini.isolate_cmd[k][i] == '<')
		{
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i] == '<')
			{
				mini.isolate_cmd[k][i] = 0;
				i++;
			}
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i] != 32)
			{
				mini.isolate_cmd[k][i] = 0;
				i++;
			}
			return ;
		}
		else
			i++;
	}
}

void	remove_outfile_simple(t_mini mini, int k)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(mini.isolate_cmd[k]))
	{
		if (mini.isolate_cmd[k][i] == '>')
		{
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i] == '>')
			{
				mini.isolate_cmd[k][i] = 0;
				i++;
			}
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i] != 32)
			{
				mini.isolate_cmd[k][i] = 0;
				i++;
			}
			return ;
		}
		else
			i++;
	}
}

void	remove_outfile(t_mini mini, int k)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(mini.isolate_cmd[k]))
	{
		if (mini.isolate_cmd[k][i] == '>' && mini.isolate_cmd[k][i] == '>')
		{
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i] == '>')
			{
				mini.isolate_cmd[k][i] = 0;
				i++;
			}
			while (mini.isolate_cmd[k][i] && mini.isolate_cmd[k][i] != 32)
			{
				mini.isolate_cmd[k][i] = 0;
				i++;
			}
			return ;
		}
		else
			i++;
	}
}