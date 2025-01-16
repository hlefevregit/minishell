/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:05:42 by dguerin           #+#    #+#             */
/*   Updated: 2025/01/15 14:30:15 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	op_options(t_token token)
{
	if (token == T_OUT_APPEND)
		return (O_WRONLY | O_APPEND | O_CREAT);
	if (token == T_OUT_TRUNCATE)
		return (O_WRONLY | O_TRUNC | O_CREAT);
	if (token == T_IN)
		return (O_RDONLY);
	return (0);
}

void	handle_redirection(t_cmd *cmd)
{
	t_list	*lst;
	t_lexer	*content;

	lst = cmd->out;
	while (lst)
	{
		content = lst->content;
		if (content->token != T_HERE_DOC)
			content->fd = open(content->str, op_options(content->token), 0777);
		if (content->fd < 0 && content->token != T_HERE_DOC)
		{
			printf("minishell: no such file or directory: %s\n", content->str);
			return ;
		}
		dup2(content->fd, content->token != T_IN);
		lst = lst->next;
	}
}

void	close_redirection(void *ptr)
{
	t_lexer	*content;

	content = ptr;
	close(content->fd);
}
