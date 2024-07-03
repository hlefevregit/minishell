/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:45:33 by hulefevr          #+#    #+#             */
/*   Updated: 2024/07/03 13:50:14 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

static void	ft_putargs(char **av)
{
	while (*av)
	{
		ft_putstr_fd(*av, 1);
		if (*(av + 1) != NULL)
			ft_putchar_fd(' ', 1);
		av++;
	}
}

static bool	ft_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
	{
		i++;
		if (str[i] != 'n')
			return (false);
		return (true);
	}
	return (false);
}

void	ft_echo(char **argv)
{
	bool	option;

	argv++;
	option = false;
	while (*argv && ft_option(*argv))
	{
		option = true;
		argv++;
	}
	ft_putargs(argv);
	if (!option)
		ft_putchar_fd('\n', 1);
}