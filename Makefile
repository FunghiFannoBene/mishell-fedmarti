NAME = minishell

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc

SRCS = minishell.c \
	loop_logic.c \
	var.c \
	var2.c \
	var3.c \
	get_env_list.c \
	env.c \
	export.c \
	print_export.c \
	cd.c \
	echo.c \
	exit.c \
	pwd.c \
	unset.c \
	heredoc.c  \
	ft_builtin.c \
	create_pipeline.c \
	sort_pipeline_tree.c \
	sort_pipeline_tree2.c \
	exec.c \
	run_command_pipeline.c \
	run_command.c \
	pipeline_util.c \
	ft_fork.c \
	program_call.c \
	redirect_input.c \
	error_messages.c \
	file_utils.c \
	transform_dollar.c \
	transform_dollar2.c \
	transform_dollar3.c \
	transform_dollar4.c \
	command_list.c \
	command_list2.c \
	command_list3.c \
	command_list4.c \
	command_list5.c \
	command_list6.c \
	command_list7.c \
	command_list8.c \
	command_list9.c \
	command_list10.c \
	command_list11.c \
	command_list12.c \

OBJS = $(SRCS:%.c=%.o)

CFLAGS = -Wall -Werror -Wextra -g

LIBS= -L$(LIBFT_DIR) -lft -lreadline

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@ $(LIBS)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@ 

clean:
	rm -f *.o */*.o

fclean: clean
	rm -f $(NAME)

re: fclean clean all

PHONY: clean fclean re all

libclean:
	make -C $(LIBFT_DIR) fclean