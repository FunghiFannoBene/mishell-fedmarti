#ifndef SHORT_CODE_H
#define SHORT_CODE_H

typedef struct s_short_dollar{
	int env_len;
	int save;
	int save_pre;
	int size;
	int slash_count;
	int start;
	int flag;
	int i;
	char *tmp;

} t_short_dollar;

typedef struct s_replace{
	int env_len;
	char *str;
	char *result;
	char *start;
	int x;
} t_replace;

typedef struct s_slashes
{
	int		i;
	int		count;
	int		x;
	char	*str;
} t_slashes;

typedef struct s_command
{
	t_redirect *command;
	t_redirect *head;
	t_pnode *structure;
	t_pnode *structure_head;
	t_pnode *structure_actual;
	t_redirect *temp;
	int i;
	int x;
	int command_record;
	int type;
} t_command;

typedef struct s_search
{
	int x;
	int start;
	t_redirect *head;
	int single_double;
	int rx;
} t_search;

#endif