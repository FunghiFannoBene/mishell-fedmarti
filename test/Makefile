SRC = env_export.c \
	../get_env_list.c \
	../var.c \
	../env.c \
	../export.c \
	../print_export.c

TEST = ./test

LIBFT = ../libft/libft.a

$(TEST): $(LIBFT)
	@gcc -g -Wall -Wextra -Werror $(SRC) $(LIBFT) -o $(TEST)

env_test: env_clean test
	./$(ENV) env > env_test_minishell
	env > env_test
	diff env_test env_test_minishell
	@echo 
	@echo End $@ test

env_clean:
	@rm -f $(TEST)
	@rm -f env_test 
	@rm -f env_test_minishell


$(LIBFT):
	make re -C ../libft

phony: env_test env_clean