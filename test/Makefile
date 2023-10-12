SRC = env_export.c \
	../get_env_list.c \
	../var.c \
	../env.c \
	../export.c \
	../print_export.c

PIP_SORT_SRC = pipeline_test.c \
	../sort_pipeline_tree.c \

PIP_SRC = ../cd.c \
	../env.c \
	../get_env_list.c \
	../export.c \
	../print_export.c \
	../pwd.c \
	../heredoc.c \
	../var.c \
	../var2.c \
	../var3.c \
	../file_utils.c \
	../unset.c \
	../error_messages.c \
	../program_call.c \
	../redirect_input.c \
	../create_pipeline.c \
	../sort_pipeline_tree.c \
	../run_command_pipeline.c \
	../pipeline_util.c \
	pipeline_test.c

TEST = ./test

PIPELINE_SORT_TEST = pipeline_sort_test

PIPELINE_TEST = piptest

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
	gcc -g $(PIP_SRC) -L../libft -lft -lreadline -o $@

$(PIPELINE_SORT_TEST): $(LIBFT)
	gcc -g $(PIP_SORT_SRC) -L../libft -lft -o $@

$(LIBFT):
	make re -C ../libft

PHONY: env_test env_clean