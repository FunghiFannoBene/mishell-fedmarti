NAME = minishell

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc

SRCS = minishell.c \
	var.c \
	get_env_list.c

CFLAGS = -Wall -Werror -Wextra -g

LIBS= -L$(LIBFT_DIR) -lft -lreadline

all: $(LIBFT)
	$(CC) $(SRCS) -g -o $(NAME) $(LIBS)

$(LIBFT):
	make -C $(LIBFT_DIR)