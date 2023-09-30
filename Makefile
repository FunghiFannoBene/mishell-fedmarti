NAME = minishell

LIBFT_DIR = libft

CC = gcc

SRCS = minishell.c \
	var.c \
	get_env_list.c

CFLAGS = -Wall -Werror -Wextra -g

LIBS= -lreadline -L$(LIBFT_DIR) -lft

all:
	$(CC) $(SRCS) -g $(LIBS) -o $(NAME)