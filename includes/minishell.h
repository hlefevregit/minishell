/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:58:19 by hulefevr          #+#    #+#             */
/*   Updated: 2024/09/02 17:48:46 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>
# include <dirent.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <sys/ioctl.h>

// # ifndef READLINE_LIBRARY 
// #  define READLINE_LIBRARY 
// # endif

# include "libft.h"
# include "get_next_line.h"

# define STDIN  STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

# define S_QUOTE 39
# define D_QUOTE 34

# define _XOPEN_SOURCE 700
# define _GNU_SOURCE

# define TRUE  1
# define FALSE 0

# define GREEN "\033[0m\033[1;32m"
# define CYAN "\033[0m\033[1;36m"
# define YELLOW "\033[0m\033[1;33m\033[3;33m"
# define RESET "\033[0m"
# define RED "\e[0;31m"

typedef enum e_token_type
{
	T_CMD,
    T_ARG,
	T_RLESS,
    T_RGREAT,
	T_DLESS,
	T_DGREAT,
    T_OR_FILE,
    T_I_FILE, 
    T_OD_FILE,
	T_PIPE,
	T_AND,
	T_OR,
	T_NL,
	T_ERR,
	T_HEREDOC,
	T_VAR,
	T_S_QUOTE,
	T_D_QUOTE,
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
	char	**isolate_cmd;
	int		size_cmd;
	int		infile;
	int		outfile;
    t_token *token;
}             t_mini;

typedef struct s_global
{
	int	exit_status;
}			t_global;

extern t_global	g_global;

/***************** UTILS ********************/

void	free_double(char **str);
int		count_array(char **arr);
char	*find_in_env(char *cmd, char **envp);
char	*find_path(char *cmd, char **envp);

/***************** LEXER *******************/

void	get_lex_of_cmd(t_mini mini);
t_mini	get_token_type(t_mini mini);
void	search_for_args(t_mini mini);
int		ft_is_cmd(char *cmd);
int		cntquotes(char *cmd);
char	**ft_split_cmd(char *s, t_mini mini);

/**************** PARSER ******************/

void	parse_cmd(t_mini mini);
char	**isolate_cmd(t_mini mini);
int		get_nb_cmd(t_mini mini);

/*************** EXEC ****************/

void	ft_exec_pipex(t_mini mini);
void	here_doc(char *limiter);
void	ft_execute(char *arg, t_mini mini);

/**************** BUILT-IN ***********/

void	ft_echo(char **argv, t_mini mini);
void	ft_cd(char **av, t_mini mini);
void	ft_pwd(t_mini mini);
void	ft_unset(char **av, t_mini mini);
void	ft_export(char **av, t_mini mini);
void	ft_env(char **argv, t_mini mini);

#endif