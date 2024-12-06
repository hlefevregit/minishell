ALL_SRCS		=	$(addprefix parsing/, $(SRCS_PARSING)) $(SRCS_UTILS) $(addprefix buildins/, $(SRCS_BULTINS))

SRCS_UTILS		=	main.c									\
					signal.c

SRCS_PARSING	=	parsing.c								\
					free.c								\
					lst.c									\
					lexer.c								\

SRCS_BULTINS	=	cd.c									\
					echo.c									\
					env.c									\
					exit.c									\
					export.c								\
					pwd.c									\
					unset.c									\
					execve.c								\
					bul_utils.c 							\

INCLUDES		=	-Iincludes								\


LD_FLAGS		=	-Llibft  -lft -ltermcap -lreadline

NAME			=	minishell
OBJS			=	$(addprefix srcs/, $(ALL_SRCS:.c=.o))

CC				=	cc
RM				=	@rm -f

LIBFT			=	libft/libft.a

FLAGS			=	-Wall -Werror -Wextra $(INCLUDES) -fsanitize=address -g

.c.o:
					@$(CC) -c $< -o $(<:.c=.o) $(FLAGS)

$(NAME):			$(LIBFT) start_message $(OBJS)
					@if [ "$?" = "start_message" ]; then echo -n "\033[1A\033[30C\033[0;33mAlready done\033[15D\033[1B\033[1A\033[2D\033[1;32m✓\033[26D\033[1B\033[0m";else echo -n "\033[1A\033[25C\033[1;32m✓\033[26D\033[1B\033[0m"; fi
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)

$(LIBFT):
					@make -s -C libft -f Makefile

all:				$(NAME)

bonus:				re

clean:
					@make -s -C libft -f Makefile clean
					@echo "\033[0;33mCleaning \033[1;31m$(NAME)\033[0;33m's objects\033[0m"
					$(RM) $(OBJS)

fclean:				clean
					@make -s -C libft -f Makefile fclean
					@echo "\033[0;33mRemoving \033[1;31m$(NAME)\033[0;33m.\033[0m"
					$(RM) $(NAME)

start_message:
					@echo "\033[0;33mMaking \033[1;31m$(NAME)\033[0;33m\t\033[1;30m[\033[1;31mX\033[1;30m]\033[0m"

re:					fclean $(LIBFT) start_message $(OBJS)
					@if [ "$?" = "fclean start_message" ]; then echo -n "\033[1A\033[30C\033[0;33mAlready done\033[15D\033[1B\033[1A\033[2D\033[1;32m✓\033[26D\033[1B\033[0m";else echo -n "\033[1A\033[25C\033[1;32m✓\033[26D\033[1B\033[0m"; fi
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)

.PHONY:				all clean fclean re
