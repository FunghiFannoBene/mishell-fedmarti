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

#endif