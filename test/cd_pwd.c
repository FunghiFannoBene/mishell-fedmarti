#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *cd = "/mnt/c/Users/Sheng/Desktop/mishell-fedmarti/";
	int size = 100;
	char *pwd = malloc(sizeof(char) * size);
	//strncmp valutare le prime parole come "comando" strncmp(input, "cd ", 3)
    chdir(cd); // cd
	getcwd(pwd, size); // pwd
	printf("pwd :%s", pwd);
	free(pwd);
    return 0;
}
