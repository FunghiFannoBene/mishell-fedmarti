/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 20:21:05 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/18 20:21:05 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../pipeline.h"


void assign_redirection(int x, t_pnode*structure)
{
	if(x == 1)
		structure->type = Redirect_input;
	else if(x == 2)
		structure->type = Redirect_input_heredoc;
	else if(x == 3)
		structure->type =  Redirect_output;
	else if(x==4)
		structure->type = Redirect_output_append;
}


int check_redirect(char *s, int *i, t_pnode* structure)
{
	int x;
	x=0;
	int flag = 0;
	int count = 0;
	structure->type = Null;
	if(s[*i] == '>' || s[*i] == '<')
	{
		if(s[*i] == '<')
			flag = '<';
		if(s[*i] == '>')
		{
			flag = '>';
			x+=2;
		}
		while(s[*i] && s[*i] == flag)
		{
			(*i)++;
			x++;
			count++;
			if(count == 2)
				break;
		}
		assign_redirection(x, structure);
		if(s[*i] == flag)
			return(1);
	}
	return(0);
}


int check_pipe(char *s, int *i, t_pnode* structure)
{
	if(s[*i] == '|')
	{
		structure->type = Pipe;
		structure->args = NULL;
		(*i)++;
		return(1);
	}
	return(0);
}

int check_virgolette_dispari(char *s, int *i)
{
	int count_double = 0;
	int count_single=0;
	int x = *i;
	while(s[x])
	{
		if(s[x] == '\'' && !(s[x] == '\\' && s[x+1] == '\''))
			count_single++;
		else if(s[x] == '"' && !(s[x] == '\\' && s[x+1] == '"'))
			count_double++;
		x++;
	}
	if(count_double % 2 || count_single % 2)
		return(-1);
	return(0);
}

int check_virgolette_dispari_start(char *s, int i)
{
	int count_double = 0;
	int count_single=0;
	int x = i;
	while(s[x])
	{
		if(s[x] == '\'' && !(s[x] == '\\' && s[x+1] == '\''))
			count_single++;
		else if(s[x] == '"' && !(s[x] == '\\' && s[x+1] == '"'))
			count_double++;
		x++;
	}
	if(count_double % 2 || count_single % 2)
		return(-1);
	return(0);
}

int    search_command(char *s, int *i, t_redirect **command, t_pnode *structure)
{
    int    x;
    int    start;
    t_redirect *head = NULL;
	int save;
	int single_double;
	single_double = 0;
    x = 0;
    *command = malloc(sizeof(t_redirect));
	memset((*command), 0, sizeof(t_redirect));
    if (!*command)
        return -1;
    while (s[*i] && s[*i] == ' ')
        (*i)++;
	if(s[*i] == '\0')
	{
		free(*command);
		return(-3);
	}
	while((s[*i] ==  '\'' && s[*i+1] ==  '\'') || (s[*i] ==  '"' && s[*i+1] ==  '"'))
		(*i)+=2;
	while (s[*i] && s[*i] == ' ')
        (*i)++;
	check_virgolette_dispari(s, i);
	if(s[*i] == '\'')
	{
		(*i)++;
		single_double = 1;
	}
	if(s[*i] == '"')
	{
		single_double = 2;
		(*i)++;
	}
	if(check_pipe(s, i, structure))
	{
		free(*command);
		*command = NULL;
		return(-4);
	}
	if(check_redirect(s, i, structure))
	{
			free(*command);
			printf("bash: syntax error near unexpected token `>'\n");
			return(-1);
	}
	while (s[*i] && s[*i] == ' ')
        (*i)++;
    head = *command;
	start = *i;
	while (s[start + x] && s[start + x] != ' ' && s[start + x] != '|' && s[start + x] != '<' && s[start + x] != '>' && s[start+x] != '\''  && s[start+x] != '"')
    	x++;
	while(((s[start+x] != '\'' && single_double == 1) && (s[start+x] != '"' && single_double == 2)))
		x++;
    (*command)->str = malloc(sizeof(char) * (x + 1));
    if (!(*command)->str)
        return -1;
    x = 0;
    while (s[*i] && s[*i] != ' ' && s[*i] != '|' && s[*i] != '<' && s[*i] != '>'  && (s[*i] != '\'' && s[*i] != '"'))
        (*command)->str[x++] = s[(*i)++];
	while(((s[*i] != '\'' && single_double == 1) && (s[*i] != '"' && single_double == 2)))
		(*command)->str[x++] = s[(*i)++];
    (*command)->str[x] = '\0';
    (*command)->size = x;
    (*command)->flag = 0;
	if(single_double)
		(*i)++;
	while (s[*i] && s[*i] == ' ')
        (*i)++;
    if(s[*i] == '\0')
    {
        (*command)->next = NULL;
		if(structure->type == Null)
			structure->type = Program_Call;
        return(-2);
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
		if(s[*i] == '\0')
			return(0);
		return (-1);
	}
	if( s[*i] == '\\' && s[*i+1] == '$')
	{
		(*command)->size+=1;
		(*command)->start += 1;
		(*i) += 2;
		return(0);
	}
	if ((*command)->flag == 0 && s[*i] == '\\' && (s[*i + 1] == '\'' || s[*i
			+ 1] == '"'))
	{
		(*command)->size++;
		(*i) += 2;
		if(s[*i] == '\0')
		{
			(*command)->start += 1;
			return(0);
		}
		return (-1);
	}
	if (s[*i] == '\\' && s[*i + 1] == '"')
	{
		(*command)->size++;
		(*i) += 2;
		return (-1);
	}
	//aggiungi qui se flag è 0 e successivo è ' o "
	return (0);
}

char *substring(const char *str, size_t begin, size_t len) 
{
    if (str == NULL || strlen(str) < begin || strlen(str) < (begin + len)) 
        return NULL; 

    return ft_strndup(str + begin, len);
}

void next_size(char *s, int *i, t_redirect **command)
{
	(*command)->flag = 0;
	(*command)->start = *i;
	(*command)->size = 0;
}

void add_and_set_for_next(t_redirect **command, char *s)
{
	(*command)->next = malloc(sizeof(t_redirect));
	memset((*command)->next, 0, sizeof(t_redirect));
	(*command)->next->str = substring(s, (*command)->start, (*command)->size);
	(*command) = (*command)->next;
	(*command)->flag = 0;
	(*command)->size = 0;
}

int	end_check(char *s, int *i, t_redirect **command)
{
	if(!s)
		return(0);
	if (s[*i] == (*command)->flag)
	{
		(*i)++;
		add_and_set_for_next(command, s);
		check_and_skip_space(s, i);
		(*command)->start = *i;
		if(s[*i] == '\0')
		{
			(*command)->next = NULL;
			return(-2);
		}
		return(-1);
	}
	else if ((*command)->flag == 0 && (s[*i] == '<' || s[*i] == '>' || s[*i] == '|'))
	{
		add_and_set_for_next(command, s);
		(*command)->start = *i;
		return(-3);
	}
	else if(s[(*i)+1] == '\0')
	{
		add_and_set_for_next(command, s);
		(*command)->next = NULL;
		(*i)++;
			return(-2);
	}
	else if((*command)->flag == 0 && (s[*i] == '\'' || s[*i] == '"') && (*command)->size)
	{
		(*i)++;
		add_and_set_for_next(command, s);
		return(-1);
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
		if(s[*i] == '\0' || s[*i] == '|' || s[*i] == '>' || s[*i] == '<')
		{
			(*command)->next = NULL;
			return(-2);
		}
		return(-1);
	}
	return(1);
}

int	size_of_command(char *s, int *i, t_redirect **head, t_pnode *structure)
{
	t_redirect *command = *head;
	int variabile;
	if(structure->type == Null)
		structure->type = Program_Call;
	command->flag = 0;
	command->start = *i;
	command->size = 0;
	while (s[*i])
	{
		check_and_skip_space(s, i);
		if(s[*i] == '\0')
			return(-1);
		if(s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
			return(0);
		if (assign_flag(s, i, &command) == -1)
			continue ;
		while (s[*i])
		{
			if (check_slashes(s, i, &command) == -1)
				continue;
			variabile = end_check(s, i, &command);
			if(variabile == -1)
				break;
			else if(variabile == -2)
				return (-1);
			else if(variabile == -3)
				return(0);
			variabile = flag_zero_space(s, i, &command);
			if(variabile == -1)
				break;
			else if(variabile == -2)
				return(1);
			if(command->flag == 0 && (s[*i] == '\'' || s[*i] == '"'))
              break;
            command->size++;
            (*i)++;
		}
	}
	return(1);
}

void free_t_pnode_list(t_pnode *structure_head) 
{
    t_pnode *current = structure_head;
    t_pnode *next_node = NULL;
    char **current_args;
    int i;

    while (current != NULL) 
	{
        next_node = current->output;
        current_args = current->args;
        
        if (current_args != NULL) {
            for (i = 0; current_args[i] != NULL; ++i) {
                free(current_args[i]);
            }
            free(current_args);
        }
        
        free(current);
        current = next_node;
    }
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
	int			type;
	command = NULL;
	structure_head = NULL;
	structure_actual = NULL;
	command_record = 0;
	head = NULL;
	i = 0;
	if(!s)
		return(NULL);
	if(check_virgolette_dispari_start(s, i))
	{
		printf("Virgolette dispari. Comando invalido.\n");
			return(NULL);
	}
	while(1)
	{
		if(s[i] == '\0')
			break;
		command = NULL;
		head = NULL;
		structure = malloc(sizeof(t_pnode));
		memset(structure, 0, sizeof(t_pnode));
		if(s[i])
		{
			type = search_command(s, &i, &command, structure);
			if(type == 0)
			{
				command_record = size_of_command(s, &i, &command, structure);
			}
			else if(type == -1)
			{
				free(structure);
				free_t_pnode_list(structure_head);
				return(NULL);
			}
			else if(type == -3)
			{
				if(structure->type == Null && !structure_head)
				{
					free(structure);
					return(NULL);
				}
				free(structure);
				return(structure_head);
			}
			else if(type == -4)
			{
				structure->args = NULL;
				structure->output = NULL;
				if(structure_actual == NULL)
				{
					structure_head=structure;
					structure_actual = structure_head;
				}
				else
				{
					structure_actual->output = structure;
					structure_actual = structure_actual->output;
				}
				continue;
			}
		}
		head = command;
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
		structure->input_fd = 0;
		structure->output_fd = 1;
		x=0;
		while(head)
		{
			structure->args[x++] = ft_strdup(head->str);
			free(head->str);
			temp = head;
			head = head->next;
			free(temp);
		}
		structure->args[x] = NULL;
		structure->output = NULL;
		if(structure_actual == NULL)
			structure_actual = structure_head;
		else
		{
	    	structure_actual->output = structure;
			structure_actual = structure_actual->output;
		}
		if(command_record == -1 || type == -2)
			break;
	}
	return(structure_head);
}


int main(void)
{
	t_pnode *head;
	t_pnode *frees;
    char *input = calloc(150, 1);
    strcpy(input, "\"          \"");
	t_data *data = malloc(sizeof(t_data));
	memset(data, 0, sizeof(t_data));
    data->export_var = NULL;
    data->local_var = NULL;

    t_var sample_vars[7];
    t_list export_nodes[7];
    t_list local_nodes[7];

    char *names[] = {"ARG", "BCD", "NAME", "VAL", "USER", "TERM"};
    char *values[] = {"123", "xyz", "Alice", "42", "test_value", "ahahah"};

	for (int i = 0; i < 6; ++i) {
		sample_vars[i].name = names[i];
		sample_vars[i].value = values[i];

		export_nodes[i].content = &sample_vars[i];
		export_nodes[i].next = i == 5 ? NULL : &export_nodes[i + 1];

		local_nodes[i].content = &sample_vars[i];
		local_nodes[i].next = i == 5 ? NULL : &local_nodes[i + 1];
	}

	data->export_var = &export_nodes[0];
	data->local_var = &local_nodes[0];

	input = transform_for_dollar(input, data);
	printf("\n\n%s\n\n", input);
	int i = 0;
    head = create_command_list(input);
	while(head)
	{
		if(head->args)
		{
			while(head->args[i])
			{
				printf("%s\n", head->args[i]);
				free(head->args[i]);
				i++;
			}
		 if(head->args[i] == NULL)
		 	printf("(null)\n");
			free(head->args);
		}
		i=0;
		printf("Type: %d \n0=Null, 1=Program_Call, 2=Pipe 3 4 5 6 redirect\n", (int)head->type);

		printf("\n\n-----------------------------------------------------------------\n\n");
		frees=head;
		head=head->output;
		free(frees);
	}
	free(data);
	free(input);
    return 0;
}
