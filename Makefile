NAME = minishell

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc

SRCS = minishell.c \
	var.c \
	var2.c \
	var3.c \
	get_env_list.c \
	env.c \
	export.c \
	print_export.c \
	cd.c \
	echo.c \
	pwd.c \
	unset.c \
	heredoc.c  \
	create_pipeline.c \
	sort_pipeline_tree.c \
	run_command_pipeline.c \
	pipeline_util.c \
	program_call.c \
	redirect_input.c \
	error_messages.c \
	file_utils.c \
	transform_dollar.c \
	command_list_new.c

CFLAGS = -Wall -Werror -Wextra -g

LIBS= -L$(LIBFT_DIR) -lft -lreadline

all: $(LIBFT)
	$(CC) $(SRCS) $(CFLAGS) -o $(NAME) $(LIBS)

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