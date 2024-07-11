/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugolefevre <hugolefevre@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:24:17 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/10 15:51:30 by hugolefevre      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	remove_infile(t_mini mini, int k)
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
			return (1);
		}
		else
			i++;
	}
	return (0);
}

int	remove_infile_simple(t_mini mini, int k)
{
	size_t	i;

	i = 0;
	printf("ft_strlen(mini.isolate_cmd[%i]) = %zu\n", k, ft_strlen(mini.isolate_cmd[k]));
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
			return (1);
		}
		else
			i++;
	}
	return (0);
}

int	remove_outfile_simple(t_mini mini, int k)
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
			return (1);
		}
		else
			i++;
	}
	return (0);
}

int	remove_outfile(t_mini mini, int k)
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
			return (0);
		}
		else
			i++;
	}
	return (1);
}