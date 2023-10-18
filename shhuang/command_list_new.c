#include "../minishell.h"
#include "../pipeline.h"

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

int	assign_flag_dollar(char *s, int *i, char *flag)
{
	if (s[*i] == '\'')
		*flag = '\'';
	else if (s[*i] == '"')
		*flag = '"';
	if (*flag != 0)
		(*i)++;
	if (*flag == s[*i])
	{
		(*i)++;
		*flag = 0;
	}
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
	if (s[*i] == '\\' && s[*i + 1] == '"' || s[*i] == '\\' && s[*i + 1] == '$')
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

int check_invalid(char c, char* invalid)
{
	int i = 0;
	while(invalid[i])
	{
		if(invalid[i] == c)
			return(1);
		i++;
	}
	return(0);
}

int checksymbol(char *s)
{
	if (s == NULL)
		return (0);
	int i = 0;
	while(s[i] != '\0')
	{
		if(check_invalid(s[i], NOT_VALID) == 1)
			return(i+1);
		i++;
	}
	return(i);
}

int checksymbol2(char *s)
{
	if (s == NULL)
		return (0);
	int i = 0;
	while(s[i] != '\0')
	{
		if(check_invalid(s[i], NOT_VALID) == 1)
			return(i+1);
		i++;
	}
	return(i+1);
}

char *add_slashes(char *tmp)
{
	if(!tmp)
		return(NULL);
	int i = 0;
	int count = 0;
	int x = 0;
	char *str;
	while(tmp[i])
	{
		if(tmp[i] == '\'' || tmp[i] == '"')
			count++;
		i++;
	}
	i=0;
	if(count == 0)
		return tmp;
	str = malloc(sizeof(char) * (ft_strlen(tmp) + count +1));
	while(tmp[x])
	{
		if(tmp[x] == '\'' || tmp[x] == '"')
		{
			str[i] = '\\';
			i++;
		}
		str[i] = tmp[x];
		x++;
		i++;
	}
	str[i] = '\0';
	free(tmp);
	return(str);
}

char *ft_strndup(const char *s, size_t n)
{
    char *result;
    size_t len = n;

    result = (char *)malloc(len + 1);
    if (!result) // If malloc failed
        return NULL;

    result[len] = '\0';
    return (char *)ft_memcpy(result, s, len);
}



char *replace_for_new_str(char* s,char* tmp, int i, int size)
{
	int env_len;
	char *str;
	char *result;
	char *start;
	int x;
	x = 0;
	env_len = checksymbol2(s+i+1);
	while(s[i])
	{
		if(s[i] == '$')
		{
			start = ft_strndup(s, i);
			if(tmp == NULL)
				result = ft_multistrjoin((char *[]) {start, s+i+env_len, NULL});
			else
				result = ft_multistrjoin((char *[]) {start, "'", tmp, "'", s+i+env_len, NULL});
			if(tmp)
			{
				free(tmp);
				tmp = NULL;
			}
			free(start);
			free(s);
			s = NULL;
			return(result);
		}
		i++;
	}
	return(s);
}


char *transform_for_dollar(char *s, t_data* data)
{
	char *tmp;
	int i = 0;
	t_var *list;
	int env_len;
	int save;
	int save_pre;
	int size;
	int slash_count;
	int start;
	int flag = 0;
	size = 0;
	
	slash_count = 0;
	while(s[i] != '\0')
	{
		tmp = NULL;
		if(s[i] == '\\')
		{
			while(s[i] == '\\')
			{
				slash_count++;
				i++;
			}
		}
		else
			slash_count = 0;
		if(s[i] == '\'')
			flag = 1;
		while(s[i] && flag == 1)
		{
			i++;
			if(s[i] == '\'')
				flag = 0;
		}
		if(s[i] == '\0')
			return(s);
		start = i;
		if(s[i] == '$' && slash_count % 2 == 0 && (env_len = checksymbol(s+i+1)))
		{
			save = s[i+env_len];
			s[i+env_len] = '\0';
			list = search_variable_tvar(s+i, data);
			s[i+env_len] = save;
			if(list != NULL)
			{
				tmp = ft_strdup(list->value);
				tmp = add_slashes(tmp);
				size = ft_strlen(tmp);
				i+=size+1;
			}
			s = replace_for_new_str(s, tmp, start, size);
		}
		i++;
	}
	return(s);
}

t_pnode *create_command_list(char *s)
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
	command = NULL;
	structure_head = NULL;
	i = 0;
	// if(strchr(s, '$') == 0)
	// 	s = transform_for_dollar(s, env);
	while(1)
	{
		search_command(s, &i, &command);
		head = command;
		command_record = size_of_command(s, &i, &command);
		structure = malloc(sizeof(t_pnode));
		if(structure_head == NULL)
			structure_head = structure;
		//structure_head
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
		structure->output = NULL;
		x=0;
		while(structure->args[x])
		{
			x++;
		}
		structure_actual = structure_head;
		x=0;

			if(structure_actual == NULL) 
			{
				structure_actual = structure;
			} 
			else 
			{		
				while(structure_actual->output != NULL) 
				{
					structure_actual = structure_actual->output;
				}
    		structure_actual->output = structure;
			}

		if(command_record == -1)
			break;
	}
	return(structure_head);
}


int main(void)
{
    t_data *data = malloc(sizeof(t_data));
	t_pnode *head;
    data->export_var = NULL;
    data->local_var = NULL;

    t_var sample_vars[6];
    t_list export_nodes[6];
    t_list local_nodes[6];

    char *names[] = {"ARG", "BCD", "NAME", "VAL", "TEST", "TERM"};
    char *values[] = {"123", "xyz", "Alice", "42", "test_value", NULL};

    for (int i = 0; i < 6; ++i) {
        sample_vars[i].name = names[i];
        sample_vars[i].value = values[i];

        export_nodes[i].content = &sample_vars[i];
        export_nodes[i].next = i == 0 ? NULL : &export_nodes[i - 1];

        local_nodes[i].content = &sample_vars[i];
        local_nodes[i].next = i == 0 ? NULL : &local_nodes[i - 1];
    }

    data->export_var = &export_nodes[4];
    data->local_var = &local_nodes[4];

    char *input = calloc(100, 1);
    strcpy(input, "echo \\$|$ARG|\\$BCD|$TERM|   $ABDD | echo1 abcd $?");
	input = transform_for_dollar(input, data);
	printf("\n\nDollaro conv:%s\n\n", input);	


	//si ferma a TERM E LOOPA CONTROL

	// int i = 0;
    // head = create_command_list(input);
	// while(head)
	// {
	// 	while(head->args[i])
	// 	{
	// 		printf("%s", head->args[i]);
	// 		printf("\n");
	// 		i++;
	// 	}
	// 	printf("%s", head->args[i]);
	// 	printf("\n");
	// 	head=head->output;
	// }
    // free(data);
    // return 0;
}

//test case: echo $ARG\\$BCD$TERM