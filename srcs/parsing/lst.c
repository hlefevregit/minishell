/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:17:35 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 15:17:36 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*lst_conv(void *content)
{
	t_lexer	*lexer;

	lexer = content;
	return (ft_strdup(lexer->str));
}

int	is_pipe(void *content)
{
	t_lexer	*lexer;

	lexer = content;
	return (lexer->token == T_PIPE);
}

int	is_arg(void *content)
{
	t_lexer	*lexer;

	lexer = content;
	return (lexer->token == T_NONE);
}
