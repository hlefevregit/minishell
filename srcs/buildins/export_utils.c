/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:35:57 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/17 20:02:56 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	bubble_sort(char **sorted_env, int *tb, int n)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (i < n - 1)
	{
		k = 0;
		while (k < n - i - 1)
		{
			if (tb[k] > tb[k + 1])
			{
				ft_swap(&tb[k], &tb[k + 1]);
				ft_swap_strings(&sorted_env[k], &sorted_env[k + 1]);
			}
			k++;
		}
		i++;
	}
}

int	count_alph(char c)
{
	int		i;
	char	a;

	a = 'a';
	i = 1;
	if (ft_isalpha(c))
		c += 32;
	while (i <= 26)
	{
		if (a == c)
			return (i);
		i++;
		a++;
	}
	return (27);
}

void	fill_index_tb(char **env, int *tb, int i)
{
	int		n;
	char	c;

	c = env[i][0];
	n = count_alph(c);
	tb[i] = n;
}

void	export_oargs(t_cmd *cmd)
{
	int		k;
	char	**sorted_env;
	int		*tb;

	k = 0;
	tb = malloc(sizeof(int) * ft_tablen(cmd->data->env));
	if (!tb)
		return ;
	sorted_env = ft_tabcpy(cmd->data->env);
	if (!sorted_env)
	{
		free(tb);
		return ;
	}
	while (k < ft_tablen(cmd->data->env))
	{
		fill_index_tb(sorted_env, tb, k);
		k++;
	}
	bubble_sort(sorted_env, tb, ft_tablen(cmd->data->env));
	ft_print_tab_fd1(sorted_env);
	ft_free_tab(sorted_env);
	free(tb);
}
