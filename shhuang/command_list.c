#include "minishell.h"

int    search_command(char *s, int *i, t_redirect **command)
{
    int    x;
    int    start;
    t_redirect *head = NULL;
  
    x = 0;
    *command = malloc(sizeof(t_redirect));
    head = *command;
    if (!*command)
        return -1;
    while (s[*i] && s[*i] == ' ')
        (*i)++;
    start = *i;
    while (s[start + x] && s[start + x] != ' ')
        x++;
    (*command)->str = malloc(sizeof(char) * (x + 1));
    if (!(*command)->str)
        return -1;
    x = 0;
    while (s[*i] && s[*i] != ' ')
        (*command)->str[x++] = s[(*i)++];
    (*command)->str[x] = '\0';
    (*command)->size = x;
    (*command)->flag = 0;
    if(s[*i] == '\0')
        {
            (*command)->next = NULL;
            return(-1);
			// FREE????? chiedere conferma di cosa fare quando echo è da solo. ad esempio o qualsiasi command
        }
    else
        next_size(s, i, &head);
    return(0);
}


int	check_and_skip_space(char *s, int *i)
{
	if (s[*i] == ' ')
	{
		while (s[*i] == ' ')
			(*i)++;
	}
	else
		return (-1);
	return(0);
}

int	assign_flag(char *s, int *i, t_redirect **command)
{
	if (s[*i] == '\'')
		(*command)->flag = '\'';
	else if (s[*i] == '"')
		(*command)->flag = '"';
	if ((*command)->flag != 0)
		(*i)++;
	if ((*command)->flag == s[*i])
	{
		(*i)++;
		(*command)->flag = 0;
		return (-1);
	}
	(*command)->start = *i;
	return (1);
}

int	check_slashes(char *s, int *i, t_redirect **command)
{
	if (((*command)->flag == 0 || (*command)->flag == '"') && s[*i] == '\\'
			&& s[*i + 1] == '\\')
	{
		(*i) += 2;
		(*command)->size++;
		return (-1);
	}
	if ((*command)->flag == 0 && s[*i] == '\\' && (s[*i + 1] == '\'' || s[*i
			+ 1] == '"'))
	{
		(*command)->size++;
		(*i) += 2;
		return (-1);
	}
	if (s[*i] == '\\' && s[*i + 1] == '"')
	{
		(*command)->size++;
		(*i) += 2;
		return (-1);
	}
	return (0);
}

char *substring(const char *str, size_t begin, size_t len) 
{
    if (str == NULL || strlen(str) < begin || strlen(str) < (begin + len)) 
        return NULL; 

    return strndup(str + begin, len);
}

void next_size(char *s, int *i, t_redirect **command)
{
	(*command)->flag = 0;
	(*command)->start = *i;
	(*command)->size = 0;
	
}

int	end_check(char *s, int *i, t_redirect **command)
{
	if (s[*i] == (*command)->flag)
	{
		(*i)++;
		(*command)->next = malloc(sizeof(t_redirect));
		(*command)->next->str = substring(s, (*command)->start, (*command)->size);
		(*command) = (*command)->next;
		(*command)->flag = 0;
		(*command)->size = 0;
		check_and_skip_space(s, i);
		(*command)->start = *i;
		if(s[*i] == '|')
		{
			(*i)++;
			(*command)->next = NULL;
			return(-2);
		}
		if(s[*i] == '\0')
		{
			(*command)->next = NULL;
			return(-3);
		}
		return(-1);
	}
	else if ((*command)->flag == 0 && s[*i] == '|')
	{
		(*i)++;
		(*command)->next = malloc(sizeof(t_redirect));
		(*command)->next->str = substring(s, (*command)->start, (*command)->size);
		(*command) = (*command)->next;
		(*command)->flag = 0;
		(*command)->size = 0;
		check_and_skip_space(s, i);
		(*command)->start = *i;
		if(s[*i] == '\0')
		{
			(*command)->next = NULL;
			return(-3);
		}
		return(-2);
	}
	else if(s[(*i)+1] == '\0')
	{
		(*command)->next = malloc(sizeof(t_redirect));
		(*command)->size++;
		(*command)->next->str = substring(s, (*command)->start, (*command)->size);
		(*command) = (*command)->next;
		(*command)->next = NULL;
			return(-3);
	}
	return 0;
}

void dollar_sign(char *s, int *i, t_redirect **command)
{
	 if(((*command)->flag == 0 || (*command)->flag == '"') && s[*i] == '$')
                (*command)->size += 0; // per ora
}

int flag_zero_space(char *s, int *i, t_redirect **command)
{

	if((*command)->flag == 0 && s[*i] == ' ')
    {
		(*command)->next = malloc(sizeof(t_redirect));
		(*command)->next->str = substring(s, (*command)->start, (*command)->size);
		(*command) = (*command)->next;
		(*command)->flag = 0;
		(*command)->size = 0;
		check_and_skip_space(s, i);
		(*command)->start = *i;
		if(s[*i] == '\0' || s[*i] == '|')
		{
			if(s[*i] == '|')
				(*i)++;
			(*command)->next = NULL;
			return(-2);
		}
		return(-1);
	}
	return(1);
}

// int dollar_sign(char *s)
// {
// 	int i;
// 	i = 0;
// 	while(s[i])
// 	{
		
// 		get_var( );

// 	}
// 	char *
// 	int i = 0;
// 	while()
// }

int	size_of_command(char *s, int *i, t_redirect **command)
{
	t_redirect *head = *command;
	int variabile;
	if (check_and_skip_space(s, i) == -1)
		return (-1);
	(*command)->flag = 0;
	(*command)->start = *i;
	(*command)->size = 0;
	while (s[*i])
	{
		check_and_skip_space(s, i);
		if (assign_flag(s, i, command) == -1)
			continue ;
		while (s[*i])
		{
			if (check_slashes(s, i, command) == -1)
				continue;
			variabile = end_check(s, i, command);
			if(variabile == -1)
				break;
			else if(variabile == -2)
				return (1);
			else if(variabile == -3)
				return (-1);
			variabile = flag_zero_space(s, i, command);
			if(variabile == -1)
				break;
			else if(variabile == -2)
				return(1);
			if((*command)->flag == 0 && (s[*i] == '\'' || s[*i] == '"'))
              break;
            (*command)->size++;
            (*i)++;
		}
	}
	return(1);
}

void	create_command_list()
{
	t_redirect	*command;
	t_redirect	*head;
	t_pnode *structure;
	t_pnode *structure_head;
	t_pnode *structure_actual;
	t_redirect *temp;
	int			i;
	int			x;
	int			command_record;
	char *s = "echo \"cat < test.c\" | wc";
	command = NULL;
	structure_head = NULL;
	i = 0;

	while(1)
	{
		search_command(s, &i, &command);
		head = command;
		command_record = size_of_command(s, &i, &command);
		structure = malloc(sizeof(t_pnode));
		if(structure_head == NULL)
			structure_head = structure;
		x=0;
		command = head;
		while(command)
		{
			x++;
			command = command->next;
		}
		structure->args = malloc(sizeof(char *) * (x + 1));
		x=0;
		while(head)
		{
			structure->args[x++] = strdup(head->str);
			temp = head;
			head = head->next;
			free(temp);
		}
		structure->args[x] = NULL;
		structure->next = NULL;
		x=0;
		while(structure->args[x])
		{
			printf("\"%s\"\n", structure->args[x++]);
		}
		printf("\"%s\"\n", structure->args[x]);
		structure_actual = structure_head;
		x=0;
		while(structure_actual->next != NULL)
		{
			structure_actual = structure_actual->next;
			x++;
		}
		if(x != 0)
			structure_actual->next = structure;
		if(command_record == -1)
			break;
	}
}

int	main(void)
{
	create_command_list();
}