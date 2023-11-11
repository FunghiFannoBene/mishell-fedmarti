#include "../minishell.h"

char	*copy_name_field(const char *var);

char	*copy_value_field(const char *var);

int main(int argc, char **argv, char **env)
{
	if (argc != 2)
	{
		printf ("give me 1 argument\n");
		return (0);
	}
	int i = 0;
	for( ; env[i] && strncmp(env[i], "PATH", 4); i++)
		;
	t_var path_var = {copy_name_field(env[i]), copy_value_field(env[i])};

	char *str = find_file_in_path(argv[1], &path_var);
	// char *str = find_file_in_path(argv[1], NULL);

	free(path_var.name);
	if (path_var.value)
		free(path_var.value);
	printf("str = \"%s\"\n", str);
	execve(str, (char *[]){argv[1], NULL}, env);
	printf("error\n");
	if (str && strncmp(argv[1], str, ft_strlen(str)))
		free(str);
}