#include "../minishell.h"

int	main(int argc, const char **argv, const char **env)
{
	t_list	*list = get_env_list(env);

	if (argc == 1)
		return (0);
	if (ft_strncmp("export", argv[1], 7) == 0)
	{
		char	**export_argv = calloc(argc, sizeof(char *));
		for (int i = 1; argv[i]; i++)
			export_argv[i - 1] = (char *)argv[i];
		ft_export(export_argv, list);
		free(export_argv);
		if (argc > 2)
			ft_export((char*[]){"export", NULL}, list);
	}
	else if (ft_strncmp("env", argv[1], 4) == 0)
		ft_env(list);
	ft_lstclear(&list, free_var);
}