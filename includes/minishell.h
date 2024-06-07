/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:58:19 by hulefevr          #+#    #+#             */
/*   Updated: 2024/06/07 18:15:01 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>
# include <dirent.h>
# include <curses.h>

// # ifndef READLINE_LIBRARY 
// #  define READLINE_LIBRARY 
// # endif

# include "libft.h"
# include "get_next_line.h"

# define STDIN  STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

# define TRUE  1
# define FALSE 0

# define IN  STDOUT
# define OUT STDIN

# define GREEN "\033[0m\033[1;32m"
# define CYAN "\033[0m\033[1;36m"
# define YELLOW "\033[0m\033[1;33m\033[3;33m"
# define RESET "\033[0m"

typedef enum e_token_type
{
	T_CMD,
    T_ARG,
	T_RLESS,
    T_RGREAT,
	T_DLESS,
	T_DGREAT,
    T_O_FILE,
    T_I_FILE,
	T_PIPE,
	T_AND,
	T_OR,
	T_NL,
	T_ERR,
	T_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
}	t_token;

typedef struct s_mini
{
    char    **envp;
    char    *cmd;
    char    **cmd_split;
    t_token *token;
}             t_mini;

#endif