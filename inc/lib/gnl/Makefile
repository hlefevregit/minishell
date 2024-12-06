# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hulefevr <hulefevr@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 12:56:19 by hulefevr          #+#    #+#              #
#    Updated: 2024/06/06 12:56:23 by hulefevr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= gcc
CFLAGS	:= -Werror -Wextra -Wall

NAME	:= get_next_line.a

SRCS	:=	get_next_line.c \
			get_next_line_utils.c \

OBJS	:= $(SRCS:.c=.o)

GREEN	:= "\033[0m\033[1;32m"
CYAN	:= "\033[0m\033[1;36m"
YELLOW	:= "\033[0m\033[1;33m\033[3;33m"
RESET	:= "\033[0m"

RM		:= rm -rf
AR		:= ar rcs

.c.o:
	@printf $(GREEN)"\r\033[KCompiling get_next_line... "$(YELLOW)"<$<> "$(RESET)"⏳ "
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I.

$(NAME): $(OBJS)
	@printf $(CYAN)"\r\033[KCompiling '$(NAME)'... "$(RESET)"⏳ "
	@$(AR) $(NAME) $(OBJS)
	@printf $(GREEN)"\r\033[KGet_next_line compiled succesfully ✅\n"$(RESET)

all: $(NAME)

clean:
	@printf $(CYAN)"\r\033[KErasing get_next_line... "$(RESET)"⏳ "
	@$(RM) $(OBJS)

fclean: clean
	@printf $(CYAN)"\r\033[KErasing $(NAME)... "$(RESET)"⏳ "
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re