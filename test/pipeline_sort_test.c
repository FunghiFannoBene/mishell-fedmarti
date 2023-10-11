#include "../pipeline.h"
#include <stdio.h>

void	print_top_row(t_pnode *head)
{
	while (head)
	{
		int len = 0;
		if (head->type == Pipe)
		{
			printf(" | ");
			head = head->output;
			continue ;
		}
		char **args = head->args;
		for (int i = 0; args[i]; i++)
		{
			len += printf("%s", args[i]);
			if (args[i + 1])
				len += printf(" ");
		}
		for ( ; len <= 20; len++)
			printf(" ");
		head = head->output;
	}
	printf("\n");
}

void	print_tree(t_pnode *head)
{
	print_top_row(head);
	while (head)
	{
		int len = 0;
		if (head->type == Pipe)
		{
			printf(" | ");
			head = head->output;
			continue ;
		}
		t_pnode *current;
		if (!head->output)
			current = NULL;
		else
			current = head->output->input[1];
		if (head->output && !current && head->output->type == Pipe)
			current = head->output->output->input[1];
		else if (current && head->type == Pipe)
			current = NULL;
		if (current)
		{
			char **args = current->args;
			for (int i = 0; args[i]; i++)
			{
				char c = 0;
				len += printf("%s", args[i]);
				if (args[i + 1])
					len += printf(" ");
			}
		}
		for ( ; len <= 20; len++)
				printf(" ");
		head = head->output;
	}
	printf("\n");
	printf("\n");
}

// cat < file | grep a << EOF

int main(void)
{

	t_pnode tree_head, node1, node2, node3, node4;

	printf("test1 :\n");

	node1 = (t_pnode){Redirect_input, (char *[]){"file", NULL}, 0 , 0, NULL, NULL, &tree_head};
	tree_head = (t_pnode){Program_Call, (char *[]){"cat", NULL}, 0 , 0, &node1, NULL, &node2};
	node2 = (t_pnode){Pipe, NULL, 0 , 0, &node1, NULL, &node3};
	node4 = (t_pnode){Redirect_input_heredoc, (char *[]){"<<", "EOF", NULL}, 0, 0, NULL, NULL, &node3};
	node3 = (t_pnode){Program_Call, (char *[]){"grep", "a", NULL}, 0 , 0, &node2, &node4, NULL};

	print_tree(&tree_head);

	print_tree(sort_pipeline_tree(&tree_head));

	printf("%ctest2 :\n", 0);
	
	tree_head = (t_pnode){Program_Call, (char *[]){"cat", NULL}, 0 , 0, {NULL, NULL}, &node1};
	node1 = (t_pnode){Redirect_input, (char *[]){"<", "file", NULL}, 0 , 0, {&tree_head, NULL}, &node2};
	node2 = (t_pnode){Pipe, NULL, 0 , 0, {&node2, NULL}, &node3};
	node3 = (t_pnode){Program_Call, (char *[]){"grep", "a", NULL}, 0 , 0, {&node3, NULL}, &node4};
	node4 = (t_pnode){Redirect_input_heredoc, (char *[]){"<<", "EOF", NULL}, 0, 0, {&node3, NULL}, NULL};

	print_tree(&tree_head);

	print_tree(sort_pipeline_tree(&tree_head));


	printf("test3 :\n");

	tree_head = (t_pnode){Program_Call, (char *[]){"cat", NULL}, 0 , 0, {NULL, NULL}, &node1};
	node1 = (t_pnode){Redirect_input, (char *[]){"<", "file", NULL}, 0 , 0, {&tree_head, NULL}, &node2};
	node2 = (t_pnode){Redirect_input_heredoc, (char *[]){"<<", "EOF", NULL}, 0 , 0, {&node2, NULL}, &node3};
	node3 = (t_pnode){Redirect_input, (char *[]){"<", "file2", NULL}, 0 , 0, {&node3, NULL}, &node4};
	node4 = (t_pnode){Redirect_input_heredoc, (char *[]){"<<", "_EOF", NULL}, 0, 0, {&node3, NULL}, NULL};

	print_tree(&tree_head);

	print_tree(sort_pipeline_tree(&tree_head));
}