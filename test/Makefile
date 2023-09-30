ENV_SRC = env_export.c \
	../get_env_list.c \
	../var.c

ENV = env

LIBFT = ../libft/libft.a

env_test: env_clean $(ENV)
	./$(ENV) > env_test_minishell
	env > env_test
	diff env_test env_test_minishell
	@echo 
	@echo End $@ test

env_clean:
	@rm -f $(ENV) 
	@rm -f env_test 
	@rm -f env_test_minishell

$(ENV): $(LIBFT)
	@gcc -g -Wall -Wextra -Werror $(ENV_SRC) $(LIBFT) -o $(ENV)

$(LIBFT):
	make re -C ../libft

phony: env_test env_clean