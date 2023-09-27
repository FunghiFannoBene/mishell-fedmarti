NAME = minishell

CC = gcc

SRCS = minishell.c \

CFLAGS = -Wall -Werror -Wextra

LIBS= -lreadline

all:
	$(CC) $(CFLAGS) $(SRCS) $(LIBS) -o $(NAME)