#include "../libft/libft.h"
#include <stdio.h>


int main(int argc, char **argv)
{
	if (argc != 3)
	{
		char str[] = "abcdefghilmnopqrstuvz";
		char charset[] = "q";
		char *substr = ft_copy_up_to(str, charset);
		printf("default test: ft_copy_up_to(%s, %s):\n%s\n", str, charset, substr);
		free(substr);
		return (0);
	}
	char *substr = ft_copy_up_to(argv[1], argv[2]);
	printf("custom test: ft_copy_up_to(%s, %s):\n%s\n", argv[1], argv[2], substr);
	free(substr);
}
