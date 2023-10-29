#include "../minishell.h"
#include "../pipeline.h"
#include "short_code.h"

int alloc_command_size(char *s, int *i, t_redirect **command, t_search *k)
{
	k->x = 0;
	while (s[*i] && s[*i] != ' ' && s[*i] != '|' && s[*i] != '<' && s[*i] != '>'
		&& (s[*i] != '\'' && s[*i] != '"'))
		(*command)->str[k->x++] = s[(*i)++];
	while (((s[*i] != '\'' && k->single_double == 1) && (s[*i] != '"'
				&& k->single_double == 2)))
		(*command)->str[k->x++] = s[(*i)++];
	(*command)->str[k->x] = '\0';
	(*command)->size = k->x;
	(*command)->flag = 0;
	if (k->single_double)
		(*i)++;
	while (s[*i] && s[*i] == ' ')
		(*i)++;
}