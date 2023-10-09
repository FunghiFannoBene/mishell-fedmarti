SRC = env_export.c \
	../get_env_list.c \
	../var.c \
	../env.c \
	../export.c \
	../print_export.c

PIP_SRC = pipeline_test.c \
	../sort_pipeline_tree.c \

TEST = ./test

PIPELINE_TEST = pipeline_test

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

find_file_test: $(LIBFT)
	gcc -Wall -Wextra -Werror -g find_file_test.c ../get_env_list.c ../file_utils.c ../var.c ../libft/libft.a -o find_file_test

$(PIPELINE_TEST): $(LIBFT)
	gcc -g $(PIP_SRC) -o $@

$(LIBFT):
	make re -C ../libft

PHONY: env_test env_clean find_file_test