/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:26:22 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/23 13:17:52 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	here_doc(char *limiter)
{
	int		tmp_fd;
	size_t	len;
	char	*line;

	tmp_fd = open("/tmp/heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			perror("readline");
			close(tmp_fd);
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		len = ft_strlen(line);
		line[len] = '\n';
		len++;
		if (write(tmp_fd, line, len) < 0)
		{
			free(line);
			perror("write");
			close(tmp_fd);
			exit(EXIT_FAILURE);
		}
		free(line);
	}
	close(tmp_fd);
	tmp_fd = open("/tmp/heredoc_tmp", O_RDONLY);
	if (tmp_fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
}
