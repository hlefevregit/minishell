/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:56:43 by hulefevr          #+#    #+#             */
/*   Updated: 2024/06/06 13:04:18 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save[32767];
	char		buffer[BUFFER_SIZE + 1];
	int			bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		add_buffer(&save[fd], buffer);
		if (there_is_a_end_of_line(save[fd]) != -1)
			return (get_line(&save[fd]));
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	return (get_line(&save[fd]));
}