CC =		gcc
CFLAGS =	-Werror -Wextra -Wall

NAME =		minishell

SRC	=		src/main.c \
			src/reste/execute.c \

OBJ =		$(SRC:.c=.o)

RM =		rm -rf

.c.o:	$(SRC)
	@$(CC) $(OFLAGS) -c $< -o $(<:.c=.o)

$(NAME)=	$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -I include/ -o $(NAME)

clean :
	@$(RM) $(OBJ)

fclean :	clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re