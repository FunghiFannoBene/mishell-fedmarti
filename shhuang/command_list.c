/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <shhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:50:06 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/30 17:50:06 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../pipeline.h"
#include "short_code.h"

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
