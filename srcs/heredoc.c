/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:26:22 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/15 14:33:24 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	here_doc(char *limiter)
{
	int		tmp_fd;
	size_t	len;
	char	*line;

	tmp_fd = open("/tmp/heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_fd < 0)
		exit(EXIT_FAILURE);
	while (1)
	{
		line = readline(CYAN"> "RESET);
		if (!line)
			exit(EXIT_FAILURE);
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		len = ft_strlen(line);
		line[len] = '\n';
		len++;
		if (write(tmp_fd, line, len) < 0)
			exit(EXIT_FAILURE);
		free(line);
	}
	close(tmp_fd);
}

void	handle_heredoc(t_cmd *cmd)
{
	t_list	*lst;
	t_lexer	*content;

	lst = cmd->out;
	while (lst)
	{
		
		content = lst->content;
		if (content->token == T_HERE_DOC)
		{
			here_doc(content->str);
			content->fd = open("/tmp/heredoc_tmp", O_RDONLY);
			if (content->fd < 0)
				return ;	
			close(content->fd);	
		}
		lst = lst->next;
	}
	
}