#ifndef MINISHELL_H
#define MINISHELL_H

// typedef struct s_shell
// {
// 	struct s_dblist *last;
// } t_shell;

// typedef struct s_dblist
// {
// 	char *old;
// 	char *actual_list_copy;

// 	struct s_dblist *next;
// 	struct s_dblist *prev;
// } t_dblist;

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