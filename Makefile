NAME = pipex

SRCS = pipex.c pipex_utils.c pipex_utils2.c main.c

OBJS = ${SRCS:.c=.o}

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror


.c.o	:
			@echo "Making $<..."
			@$(CC) -c $< -o $(<:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			@echo "     - Compiling $(NAME)..."
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "- Compiled -"

clean	:
			@echo "     - Removing object files..."
			@$(RM) $(OBJS) $(BOBJS)

fclean	:	clean
			@echo "     - Removing $(NAME)..." $(NONE)
			@$(RM) $(NAME)

re		:	fclean all