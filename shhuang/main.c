/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <shhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:12:57 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/31 15:14:31 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
// #include "../pipeline.h"
// #include "short_code.h"

// int	main(int argc, char **argv)
// {
// 	t_pnode	*head;
// 	t_pnode	*frees;
// 	char	*input;
// 	t_data	*data;
// 	t_var	sample_vars[7];
// 	t_list	export_nodes[7];
// 	t_list	local_nodes[7];
// 	char	*names[] = {"ARG", "BCD", "NAME", "VAL", "USER", "TERM"};
// 	char	*values[] = {"123", "xyz", "Alice", "42", "test_value", "ahahah"};
// 	int		i;

// 	(void)argc;
// 	input = argv[1];
// 	data = malloc(sizeof(t_data));
// 	memset(data, 0, sizeof(t_data));
// 	data->export_var = NULL;
// 	data->local_var = NULL;
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
// 	i = 0;
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
// 		printf("\n\n---------------------------------
// --------------------------------\n\n");
// 		frees = head;
// 		head = head->output;
// 		free(frees);
// 	}
// 	free(data);
// 	return (0);
// }
