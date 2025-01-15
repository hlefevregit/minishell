/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:45:45 by hulefevr          #+#    #+#             */
/*   Updated: 2024/12/23 14:54:52 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*store_file(int fd)
{
	char			buffer[11];
	int				read_return;
	char			*file_content;

	file_content = NULL;
	read_return = 1;
	while (read_return)
	{
		read_return = read(fd, buffer, 10);
		buffer[read_return] = 0;
		ft_strjoin_to(&file_content, buffer);
	}
	close(fd);
	return (file_content);
}
