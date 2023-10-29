/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/10/18 20:21:05 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/18 20:21:05 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../pipeline.h"
#include "short_code.h"

void	assign_redirection(int x, t_pnode *structure)
{
	if (x == 1)
		structure->type = Redirect_input;
	else if (x == 2)
		structure->type = Redirect_input_heredoc;
	else if (x == 3)
		structure->type = Redirect_output;
	else if (x == 4)
		structure->type = Redirect_output_append;
}

void	check_redirect_init(int *x, int *flag, int *count, t_pnode **structure)
{
	*count = 0;
	*flag = 0;
	*x = 0;
	(*structure)->type = Null;
}

int	check_redirect(char *s, int *i, t_pnode *structure)
{
	int	x;
	int	flag;
	int	count;

	check_redirect_init(&x, &flag, &count, &structure);
	if (s[*i] == '>' || s[*i] == '<')
	{
		flag = s[*i];
		if (s[*i] == '>')
		{
			x += 2;
		}
		while (s[*i] && s[*i] == flag)
		{
			(*i)++;
			x++;
			if (++count == 2)
				break ;
		}
		assign_redirection(x, structure);
		if (s[*i] == flag)
			return (1);
	}
	return (0);
}

int	check_pipe(char *s, int *i, t_pnode *structure)
{
	if (s[*i] == '|')
	{
		structure->type = Pipe;
		structure->args = NULL;
		(*i)++;
		return (1);
	}
	return (0);
}

int	check_virgolette_dispari(char *s, int *i)
{
	int	count_double;
	int	count_single;
	int	x;

	x = *i;
	count_single = 0;
	count_double = 0;
	while (s[x])
	{
		if (s[x] == '\'' && !(s[x] == '\\' && s[x + 1] == '\''))
			count_single++;
		else if (s[x] == '"' && !(s[x] == '\\' && s[x + 1] == '"'))
			count_double++;
		x++;
	}
	if (count_double % 2 || count_single % 2)
		return (-1);
	return (0);
}

int	check_virgolette_dispari_start(char *s, int i)
{
	int	count_double;
	int	count_single;
	int	x;

	count_double = 0;
	count_single = 0;
	x = i;
	while (s[x])
	{
		if (s[x] == '\'' && !(s[x] == '\\' && s[x + 1] == '\''))
			count_single++;
		else if (s[x] == '"' && !(s[x] == '\\' && s[x + 1] == '"'))
			count_double++;
		x++;
	}
	if (count_double % 2 || count_single % 2)
		return (-1);
	return (0);
}

void	init_search(t_search *k, t_redirect **command, char *s, int *i)
{
	k->x = 0;
	k->rx = 0;
	k->start = 0;
	k->head = NULL;
	k->single_double = 0;
	*command = malloc(sizeof(t_redirect));
	memset((*command), 0, sizeof(t_redirect));
	while (s[*i] && s[*i] == ' ')
		(*i)++;
}

int	check_zero_move(char *s, int *i, t_redirect **command, t_search *k)
{
	if (s[*i] == '\0')
	{
		free(*command);
		return (1);
	}
	while ((s[*i] == '\'' && s[*i + 1] == '\'') || (s[*i] == '"' && s[*i
				+ 1] == '"'))
		(*i) += 2;
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	check_virgolette_dispari(s, i);
	if (s[*i] == '\'')
	{
		(*i)++;
		k->single_double = 1;
	}
	if (s[*i] == '"')
	{
		k->single_double = 2;
		(*i)++;
	}
	return (0);
}

int	check_pipe_redi(char *s, int *i, t_redirect **command, t_pnode *structure)
{
	if (check_pipe(s, i, structure))
	{
		free(*command);
		*command = NULL;
		return (-4);
	}
	if (check_redirect(s, i, structure))
	{
		free(*command);
		printf("bash: syntax error near unexpected token `>'\n");
		return (-1);
	}
	return (0);
}

int	create_command_size(char *s, int *i, t_redirect **command, t_search *k)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	k->head = *command;
	k->start = *i;
	while (s[k->start + k->x] && s[k->start + k->x] != ' '
		&& s[k->start + k->x] != '|'
		&& s[k->start + k->x] != '<'
		&& s[k->start + k->x] != '>'
		&& s[k->start + k->x] != '\''
		&& s[k->start + k->x] != '"')
		k->x++;
	while (((s[k->start + k->x] != '\'' && k->single_double == 1)
			&& (s[k->start + k->x] != '"'
				&& k->single_double == 2)))
		k->x++;
	(*command)->str = malloc(sizeof(char) * (k->x + 1));
	if (!(*command)->str)
		return (1);
	return (0);
}

void	alloc_command_size(char *s, int *i, t_redirect **command, t_search *k)
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

int	search_command(char *s, int *i, t_redirect **command, t_pnode *structure)
{
	t_search	k;

	init_search(&k, command, s, i);
	if (check_zero_move(s, i, command, &k))
		return (-3);
	k.rx = check_pipe_redi(s, i, command, structure);
	if (k.rx != 0)
		return (k.rx);
	if (create_command_size(s, i, command, &k))
		return (-1);
	alloc_command_size(s, i, command, &k);
	if (s[*i] == '\0')
	{
		(*command)->next = NULL;
		if (structure->type == Null)
			structure->type = Program_Call;
		return (-2);
	}
	else
		next_size(i, &k.head);
	return (0);
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
	return (0);
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

int	slash_return(char *s, int *i, t_redirect **command)
{
	if ((*command)->flag == 0 && s[*i] == '\\' && (s[*i + 1] == '\'' || s[*i
				+ 1] == '"'))
	{
		(*command)->size++;
		(*i) += 2;
		if (s[*i] == '\0')
		{
			(*command)->start += 1;
			return (0);
		}
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

int	check_slashes(char *s, int *i, t_redirect **command)
{
	if (((*command)->flag == 0 || (*command)->flag == '"') && s[*i] == '\\'
		&& s[*i + 1] == '\\')
	{
		(*i) += 2;
		(*command)->size++;
		if (s[*i] == '\0')
			return (0);
		return (-1);
	}
	if (s[*i] == '\\' && s[*i + 1] == '$')
	{
		(*command)->size += 1;
		(*command)->start += 1;
		(*i) += 2;
		return (0);
	}
	return ((slash_return(s, i, command)));
}

char	*substring(const char *str, size_t begin, size_t len)
{
	if (str == NULL || strlen(str) < begin || strlen(str) < (begin + len))
		return (NULL);
	return (ft_strndup(str + begin, len));
}

void	next_size(int *i, t_redirect **command)
{
	(*command)->flag = 0;
	(*command)->start = *i;
	(*command)->size = 0;
}

void	add_and_set_for_next(t_redirect **command, char *s)
{
	(*command)->next = malloc(sizeof(t_redirect));
	memset((*command)->next, 0, sizeof(t_redirect));
	(*command)->next->str = substring(s, (*command)->start, (*command)->size);
	(*command) = (*command)->next;
	(*command)->flag = 0;
	(*command)->size = 0;
}

int	end_check_flag_zero(char *s, int *i, t_redirect **command)
{
	if ((*command)->flag == 0 && (s[*i] == '<' || s[*i] == '>'
			|| s[*i] == '|'))
	{
		add_and_set_for_next(command, s);
		(*command)->start = *i;
		return (-3);
	}
	else if (s[(*i) + 1] == '\0')
	{
		(*command)->size++;
		add_and_set_for_next(command, s);
		(*command)->next = NULL;
		(*i)++;
		return (-2);
	}
	else if ((*command)->flag == 0 && (s[*i] == '\'' || s[*i] == '"')
		&& (*command)->size)
	{
		(*i)++;
		add_and_set_for_next(command, s);
		return (-1);
	}
	return (0);
}

int	end_check(char *s, int *i, t_redirect **command)
{
	if (!s)
		return (0);
	if (s[*i] == (*command)->flag)
	{
		(*i)++;
		add_and_set_for_next(command, s);
		check_and_skip_space(s, i);
		(*command)->start = *i;
		if (s[*i] == '\0')
		{
			(*command)->next = NULL;
			return (-2);
		}
		return (-1);
	}
	return (end_check_flag_zero(s, i, command));
}

int	flag_zero_space(char *s, int *i, t_redirect **command)
{
	if ((*command)->flag == 0 && s[*i] == ' ')
	{
		(*command)->next = malloc(sizeof(t_redirect));
		(*command)->next->str = substring(s, (*command)->start,
				(*command)->size);
		(*command) = (*command)->next;
		(*command)->flag = 0;
		(*command)->size = 0;
		check_and_skip_space(s, i);
		(*command)->start = *i;
		if (s[*i] == '\0' || s[*i] == '|' || s[*i] == '>' || s[*i] == '<')
		{
			(*command)->next = NULL;
			return (-2);
		}
		return (-1);
	}
	return (1);
}

void	init_size_of_command(t_pnode *structure, t_redirect **command,
		t_redirect **head, int *i)
{
	*command = *head;
	if (structure->type == Null)
		structure->type = Program_Call;
	(*command)->flag = 0;
	(*command)->start = *i;
	(*command)->size = 0;
}

int	break_or_add(char *s, int *i, t_redirect *command)
{
	if (command->flag == 0 && (s[*i] == '\'' || s[*i] == '"'))
		return (1);
	command->size++;
	(*i)++;
	return (0);
}

int	skip_and_endstring(char *s, int *i)
{
	check_and_skip_space(s, i);
	if (s[*i] == '\0')
		return (1);
	return (0);
}

int	check_all_end(char *s, int *i, t_redirect **command, int *variabile)
{
	*variabile = end_check(s, i, command);
	if (*variabile == -1)
		return (-2);
	else if (*variabile == -2)
		return (-1);
	else if (*variabile == -3)
		return (0);
	*variabile = flag_zero_space(s, i, command);
	if (*variabile == -1)
		return (-2);
	if (*variabile == -2)
		return (1);
	return (2);
}

int	size_of_command(char *s, int *i, t_redirect **head, t_pnode *structure)
{
	t_redirect	*command;
	int			variabile;

	init_size_of_command(structure, &command, head, i);
	while (s[*i])
	{
		if (skip_and_endstring(s, i))
			return (-1);
		if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
			return (0);
		if (assign_flag(s, i, &command) == -1)
			continue ;
		while (s[*i])
		{
			if (check_slashes(s, i, &command) == -1)
				continue ;
			variabile = check_all_end(s, i, &command, &variabile);
			if (variabile == -1 || variabile == 0 || variabile == 1)
				return (variabile);
			else if (variabile == -2 || break_or_add(s, i, command))
				break ;
		}
	}
	return (1);
}

void	free_t_pnode_list(t_pnode *structure_head)
{
	t_pnode	*current;
	t_pnode	*next_node;
	char	**current_args;
	int		i;

	i = -1;
	next_node = NULL;
	current = structure_head;
	while (current != NULL)
	{
		next_node = current->output;
		current_args = current->args;
		if (current_args != NULL)
		{
			while (current_args[++i] != NULL)
			{
				free(current_args[i]);
			}
			free(current_args);
		}
		free(current);
		current = next_node;
	}
}

int	init_command(t_command *c, char *s)
{
	c->command = NULL;
	c->structure_head = NULL;
	c->structure_actual = NULL;
	c->command_record = 0;
	c->head = NULL;
	c->i = 0;
	if (!s)
		return (-1);
	if (check_virgolette_dispari_start(s, c->i))
	{
		printf("Virgolette dispari. Comando invalido.\n");
		return (-1);
	}
	return (1);
}

int	check_continuation(char *s, t_command *c)
{
	if (s[c->i] == '\0')
		return (1);
	c->command = NULL;
	c->head = NULL;
	c->structure = malloc(sizeof(t_pnode));
	memset(c->structure, 0, sizeof(t_pnode));
	return (0);
}

void	assign_structure(t_command *c)
{
	c->structure->args = NULL;
	c->structure->output = NULL;
	if (c->structure_actual == NULL)
	{
		c->structure_head = c->structure;
		c->structure_actual = c->structure_head;
	}
	else
	{
		c->structure_actual->output = c->structure;
		c->structure_actual = c->structure_actual->output;
	}
}

int	is_void(t_command *c)
{
	if (c->structure->type == Null && !c->structure_head)
	{
		free(c->structure);
		return (1);
	}
	return (0);
}

int	evaluate_next_struct(t_command *c, char *s)
{
	c->type = search_command(s, &c->i, &c->command, c->structure);
	if (c->type == 0)
		c->command_record = size_of_command(s, &c->i, &c->command,
				c->structure);
	else if (c->type == -1)
	{
		free(c->structure);
		free_t_pnode_list(c->structure_head);
		return (0);
	}
	else if (c->type == -3)
	{
		if (is_void(c))
			return (0);
		free(c->structure);
		return (1);
	}
	else if (c->type == -4)
	{
		assign_structure(c);
		return (-2);
	}
	return (3);
}

void	command_to_structure(t_command *c)
{
	c->head = c->command;
	if (c->structure_head == NULL)
		c->structure_head = c->structure;
	c->x = 0;
	c->command = c->head;
	while (c->command)
	{
		c->x++;
		c->command = c->command->next;
	}
	c->structure->args = malloc(sizeof(char *) * (c->x + 1));
	c->structure->input_fd = 0;
	c->structure->output_fd = 1;
	c->x = 0;
	while (c->head)
	{
		c->structure->args[c->x++] = ft_strdup(c->head->str);
		free(c->head->str);
		c->temp = c->head;
		c->head = c->head->next;
		free(c->temp);
	}
	c->structure->args[c->x] = NULL;
	c->structure->output = NULL;
}

void	structure_linking(t_command *c)
{
	if (c->structure_actual == NULL)
		c->structure_actual = c->structure_head;
	else
	{
		c->structure_actual->output = c->structure;
		c->structure_actual = c->structure_actual->output;
	}
}

t_pnode	*create_command_list(char *s)
{
	t_command	c;

	if (init_command(&c, s) == -1)
		return (NULL);
	while (1)
	{
		if (check_continuation(s, &c))
			break ;
		c.x = evaluate_next_struct(&c, s);
		if (c.x == -2)
			continue ;
		else if (c.x == 0)
			return (NULL);
		else if (c.x == 1)
			return (c.structure_head);
		command_to_structure(&c);
		structure_linking(&c);
		if (c.command_record == -1 || c.type == -2)
			break ;
	}
	return (c.structure_head);
}

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	t_pnode *head;
// 	t_pnode *frees;
// 	char *input = argv[1];
// 	t_data *data = malloc(sizeof(t_data));
// 	memset(data, 0, sizeof(t_data));
// 	data->export_var = NULL;
// 	data->local_var = NULL;

// 	t_var sample_vars[7];
// 	t_list export_nodes[7];
// 	t_list local_nodes[7];

// 	char *names[] = {"ARG", "BCD", "NAME", "VAL", "USER", "TERM"};
// 	char *values[] = {"123", "xyz", "Alice", "42", "test_value", "ahahah"};

// 	for (int i = 0; i < 6; ++i)
// 	{
// 		sample_vars[i].name = names[i];
// 		sample_vars[i].value = values[i];

// 		export_nodes[i].content = &sample_vars[i];
// 		export_nodes[i].next = i == 5 ? NULL : &export_nodes[i + 1];

// 		local_nodes[i].content = &sample_vars[i];
// 		local_nodes[i].next = i == 5 ? NULL : &local_nodes[i + 1];
// 	}

// 	data->export_var = &export_nodes[0];
// 	data->local_var = &local_nodes[0];

// 	input = transform_for_dollar(input, data);
// 	int i = 0;
// 	head = create_command_list(input);
// 	while (head)
// 	{
// 		if (head->args)
// 		{
// 			while (head->args[i])
// 			{
// 				printf("%s\n", head->args[i]);
// 				free(head->args[i]);
// 				i++;
// 			}
// 			if (head->args[i] == NULL)
// 				printf("(null)\n");
// 			free(head->args);
// 		}
// 		i = 0;
// 		printf("Type: %d \n0=Null, 1=Program_Call, 2=Pipe 3 4 5 6 redirect\n",
// 			(int)head->type);

// 		printf("\n\n-----------------------------------------------------------------\n\n");
// 		frees = head;
// 		head = head->output;
// 		free(frees);
// 	}
// 	free(data);
// 	return (0);
// }
