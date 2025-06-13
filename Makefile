NAME		:= pipex
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g3
SRCS		:= pipex.c pipex_errors.c pipex_exec.c pipex_path.c
OBJS		:= $(SRCS:.c=.o)
MAKEFLAGS	+= --no-print-directory

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all