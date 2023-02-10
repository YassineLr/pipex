NAME = pipex

SRCS = pipex.c pipex_utils.c pipex_utils2.c main.c

OBJS = ${SRCS:.c=.o}

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

NONE	=	'\033[0m'
GREEN	=	'\033[33m'
GRAY	=	'\033[2;37m'
ITALIC	=	'\033[3m'
UNDERLINE	=	'\033[4m'
RED	=	'\033[91m'

# Green="\e[1;32m"

# Blue=$'\e[1;34m'


.c.o	:
			@echo "Making $<..." 
			@$(CC) -c $< -o $(<:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			@echo "     → Compiling $(NAME)..."
			@$(CC) $(OBJS) -o $(NAME)
			@echo ${GREEN}"***** ***** ***** ***** *** *    **** ****" 
			@echo ${GREEN}"*     *   * * * * *   *  *  *    *    *   *" 
			@echo ${GREEN}"*     *   * * * * *****  *  *    **** *   *" 
			@echo ${GREEN}"*     *   * * * * *      *  *    *    *   *" 
			@echo ${GREEN}"***** ***** * * * *     *** **** **** ****" 


clean	:
			@echo ${RED} "     - Removing object files..."
			@$(RM) $(OBJS) $(BOBJS)

fclean	:	clean
			@echo "     - Removing $(NAME)..." $(NONE)
			@$(RM) $(NAME)

re		:	fclean all