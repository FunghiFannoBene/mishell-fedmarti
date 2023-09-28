NAME = minishell

CC = gcc

SRCS = minishell.c \

CFLAGS = -Wall -Werror -Wextra -g

LIBS= -lreadline

all:
	$(CC) $(SRCS) -g $(LIBS) -o $(NAME)