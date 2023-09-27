#ifndef MINISHELL_H
#define MINISHELL_H

typedef struct s_shell
{
	
	struct s_dblist *last;
} t_shell;

typedef struct s_dblist
{
	char *old;
	char *actual_list_copy;

	struct s_dblist *next;
	struct s_dblist *prev;
} t_dblist;

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#endif