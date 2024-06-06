# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 12:52:41 by hulefevr          #+#    #+#              #
#    Updated: 2024/06/06 16:24:44 by hulefevr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation variables
CC		:= gcc
FLAGS	:= -Lvendor/readline/lib -lreadline -ltinfo -g
CFLAGS	:= -Werror -Wextra -Wall -g -fsanitize=address

# Name of the final executable
NAME	:= minishell

SRC		:= ./src/minishell.c \

OBJ		:= $(SRC:.c=.o)

# All needed library
LIB		:=	lib/libft/libft.a \
			lib/get_next_line/get_next_line.a \

# Colors for differents prints
GREEN	:= "\033[0m\033[1;32m"
CYAN	:= "\033[0m\033[1;36m"
YELLOW	:= "\033[0m\033[1;33m\033[3;33m"
RESET	:= "\033[0m"

# Compile all .c files
.c.o: $(SRC)
	@printf $(GREEN)"\r\033[KCompiling objects... "$(YELLOW)"<$<> ⏳ "$(RESET)
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

# Compile all .o files
$(NAME): vendor/readline $(OBJ)
	@printf $(GREEN)"\r\033[KObjects compiled succesfully ✅\n"$(RESET)
	@make -C lib/libft
	@make -C lib/get_next_line
	@printf $(CYAN)"\r\033[KCompiling '$(NAME)'... ⏳"$(RESET)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(FLAGS) -I includes/ -o $(NAME)
	@printf $(GREEN)"\r\033[KSuccess compiling '$(NAME)' ✅\n"$(RESET)
	@printf "\n"

	# Readline
vendor/readline: vendor
	@if [ ! -d "vendor/readline" ]; then \
		printf $(CYAN)"\r\033[KInstallation of readline... ⏳\n"$(RESET); \
		curl https://raw.githubusercontent.com/noalexan/minishell/stable/install_readline.sh | sh; \
	fi

# Vendor
vendor:
	@mkdir vendor

# Default command to launch
all: $(NAME) 

# Compile and run minishell
run: all
	@./$(NAME)

# Just a cute loading bar
load:
	@printf '\r █▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ - 0%%\r'
	@sleep .1
	@printf '\r ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ - 5%%\r'
	@sleep .1
	@printf '\r ███▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ - 10%%\r'
	@sleep .1
	@printf '\r ████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ - 15%%\r'
	@sleep .1
	@printf '\r █████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ - 20%%\r'
	@sleep .1
	@printf '\r ██████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ - 25%%\r'
	@sleep .1
	@printf '\r ███████▒▒▒▒▒▒▒▒▒▒▒▒▒▒ - 30%%\r'
	@sleep .1
	@printf '\r ████████▒▒▒▒▒▒▒▒▒▒▒▒▒ - 35%%\r'
	@sleep .1
	@printf '\r █████████▒▒▒▒▒▒▒▒▒▒▒▒ - 40%%\r'
	@sleep .1
	@printf '\r ██████████▒▒▒▒▒▒▒▒▒▒▒ - 45%%\r'
	@sleep .1
	@printf '\r ███████████▒▒▒▒▒▒▒▒▒▒ - 50%%\r'
	@sleep .1
	@printf '\r ████████████▒▒▒▒▒▒▒▒▒ - 55%%\r'
	@sleep .1
	@printf '\r █████████████▒▒▒▒▒▒▒▒ - 60%%\r'
	@sleep .1
	@printf '\r ██████████████▒▒▒▒▒▒▒ - 65%%\r'
	@sleep .1
	@printf '\r ███████████████▒▒▒▒▒▒ - 70%%\r'
	@sleep .1
	@printf '\r ████████████████▒▒▒▒▒ - 75%%\r'
	@sleep .1
	@printf '\r █████████████████▒▒▒▒ - 80%%\r'
	@sleep .1
	@printf '\r ██████████████████▒▒▒ - 85%%\r'
	@sleep .1
	@printf '\r ███████████████████▒▒ - 90%%\r'
	@sleep .1
	@printf '\r ████████████████████▒ - 95%%\r'
	@sleep .1
	@printf '\r █████████████████████ - 100%%\r'
	@sleep .8

# Clean all .o and .a files
clean:
	@printf $(CYAN)"\r\033[KErasing objects... "$(RESET)"⏳ "
	@rm -rdf $(OBJ)
	@make -C lib/libft clean
	@make -C lib/get_next_line clean
	@printf $(GREEN)"\r\033[Kcleaned 🗑\n"$(RESET)

# Same as 'clean' but clean minishell too
fclean:
	@printf $(CYAN)"\r\033[KErasing objects... "$(RESET)"⏳ "
	@rm -rdf $(OBJ)
	@make -C lib/libft fclean
	@make -C lib/get_next_line fclean
	@printf $(GREEN)"\r\033[KObjects cleaned 🗑\n"$(RESET)
	@printf $(CYAN)"\r\033[KErasing binary file... "$(RESET)"⏳ "
	@rm -rdf $(NAME) test_parser
	@printf $(GREEN)"\r\033[KBinary file cleaned 🗑\n"$(RESET)
	@printf $(GREEN)"\r\033[KForce cleaned 🗑\n"$(RESET)

# Clean readline
fclean_readline:
	@printf $(CYAN)"\r\033[KErasing readline... "$(RESET)"⏳ "
	@rm -rdf vendor
	@printf $(GREEN)"\r\033[KReadline cleaned 🗑\n"$(RESET)

# Clean all and recompile minishell
re: fclean all

.PHONY: all clean fclean re load fclean_readline run readline