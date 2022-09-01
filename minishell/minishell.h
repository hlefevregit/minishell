/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:41:36 by marvin            #+#    #+#             */
/*   Updated: 2022/08/10 19:41:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell$"

/**********************MAIN********************/

void	loop_prompt(t_list *list)

/*********************AUTRES*******************/

void	execute(t_mini shell);

/********************UTILS***********************/

t_list	*init_list(char **env);

char	*char_toa(char c);

#endif