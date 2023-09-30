#ifndef MINISHELL_H
#define MINISHELL_H

typedef struct s_list_env
{
	char* env;
	struct s_list_env *next;
} t_env;

typedef struct s_env_pointer
{
	struct s_list_env *head;
	struct s_list_env *last;
} t_env_pointer;

#include <stddef.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h> //path max
#include <sys/types.h>
#include <sys/wait.h>

#endif