#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char* input;
	
    while (1) {
        input = readline("Minishell> "); //stampa e aspetta un input
        if (strcmp(input, "exit") == 0) {
            break;
        }
		else if(strcmp(input, "clear") == 0)
		{
			 write(STDOUT_FILENO, "\033[H\033[2J\033[3J", 11); 
			 //esegue clear "\033[H" si muove a HOME , "\033[2J" pulisce 
			 //l'area attuale "\033[3J" pulisce anche la history
		}
        printf("You entered: %s\n", input);

        add_history(input); // aggiunge alla storia da solo!
        free(input);
    }

    return 0;
}