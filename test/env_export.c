#include "../minishell.h"

int	main(int argc, const char **argv, const char **env)
{
	t_list	*list = get_env_list(env);
	(void)argv;
	(void)argc;
	while (list)
	{
		t_var *var = list->content;
		printf("%s=%s\n", var->name, var->value);
		(void)var;
		list = ft_lstnext_and_delete(list, free_var);
	}
}