NAME = minishell

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc

SRCS = minishell.c \
	var.c \
	get_env_list.c \
	env.c \
	export.c \
	print_export.c \
	cd.c \
	pwd.c

CFLAGS = -Wall -Werror -Wextra -g

LIBS= -L$(LIBFT_DIR) -lft -lreadline

all: $(LIBFT)
	$(CC) $(SRCS) -o $(NAME) $(LIBS)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f *.o */*.o

fclean: clean
	rm -f $(NAME)

re: fclean clean all

PHONY: clean fclean re all

libclean:
	make -C $(LIBFT_DIR) fclean