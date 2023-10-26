#include "../pipeline.h"
#include "../minishell.h"

int	run_command_pipeline(t_pnode *pipeline_tree, t_data *data);

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->exit_status)
		free_var(data->exit_status);
	if (data->export_var)
		ft_lstclear(&data->export_var, free_var);
	free(data);
}

// int	main(int argc, const char **argv, const char **env)
// {
// 	char	**args;

// 	(void)argc;
// 	(void)argv;

// 	args = ft_calloc(3, sizeof(char *));
// 	args[0] = ft_strdup("cat");
// 	args[1] = ft_strdup("../cd.c"); 
// 	t_pnode *head = node_create(Program_Call, args, NULL);

// 	head->output = node_create(Pipe, NULL, head);

// 	args = ft_calloc(3, sizeof(char *));
// 	args[0] = ft_strdup("grep");
// 	args[1] = ft_strdup("c");
// 	head->output->output = node_create(Program_Call, args, head->output);

// 	t_data *data = ft_calloc(1, sizeof(*data));
// 	data->exit_status = new_var("?", "0");
// 	data->export_var = get_env_list(env);
//  	printf("exit status = %i\n", run_command_pipeline(head, data));
// 	free_data(data);
// }

/*                */

// int	main(int argc, const char **argv, const char **env)
// {
// 	char	**args;
// 	t_pnode	*node = NULL;
// 	(void)argc;
// 	(void)argv;
 
// 	args = ft_calloc(2, sizeof(char *));
// 	args[0] = ft_strdup("cat");
// 	t_pnode *head = node_create(Program_Call, args, NULL);
// 	node = head;

// 	args = ft_calloc(2, sizeof(char *));
// 	args[0] = ft_strdup("../cd.c");
// 	head->output = node_create(Redirect_input, args, node);
// 	node = node->output;

// 	node->output = node_create(Pipe, NULL, node);
// 	node = node->output;

// 	args = ft_calloc(3, sizeof(char *));
// 	args[0] = ft_strdup("grep");
// 	args[1] = ft_strdup("c");
// 	node->output = node_create(Program_Call, args, node);
// 	node = node->output;


// 	args = ft_calloc(2, sizeof(char *));
// 	args[0] = ft_strdup("ntestfile");
// 	node->output = node_create(Redirect_output_append, args, node);
	
// 	t_data *data = ft_calloc(1, sizeof(*data));
// 	data->exit_status = new_var("?", "0");
// 	data->export_var = get_env_list(env);
//  	printf("exit status = %i\n", run_command_pipeline(head, data));

// 	free_data(data);
// }


/*    */

// int	main(int argc, const char **argv, const char **env)
// {
// 	char	**args;
// 	t_pnode *head = NULL; 
// 	t_pnode	*node = head;
// 	(void)argc;
// 	(void)argv;

// 	args = ft_calloc(4, sizeof(char *));
// 	args[0] = ft_strdup("grep");
// 	args[1] = ft_strdup("c");
// 	args[2] = ft_strdup("/dev/null");
// 	head = node_create(Program_Call, args, NULL);
// 	node = head;

// 	args = ft_calloc(2, sizeof(char *));
// 	args[0] = ft_strdup("ntestfile");
// 	node->output = node_create(Redirect_output, args, node);
	
// 	t_data *data = ft_calloc(1, sizeof(*data));
// 	data->exit_status = new_var("?", "0");
// 	data->export_var = get_env_list(env);
//  	printf("exit status = %i\n", run_command_pipeline(head, data));

// 	free_data(data);
// }


/*           */



int	main(int argc, const char **argv, const char **env)
{
	char	**args;
	t_pnode *head = NULL; 
	(void)argc;
	(void)argv;

	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);

	args = ft_calloc(3, sizeof(char *));
	args[0] = ft_strdup("grep");
	args[1] = ft_strdup("c");
	head = node_create(Program_Call, args, NULL);

	t_data *data = ft_calloc(1, sizeof(*data));
	data->exit_status = new_var("?", "0");
	data->export_var = get_env_list(env);
 	printf("exit status = %i\n", run_command_pipeline(head, data));

	free_data(data);
}