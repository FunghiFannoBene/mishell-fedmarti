/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <shhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:14:43 by shhuang           #+#    #+#             */
/*   Updated: 2023/09/27 20:06:09 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// IMPLEMENTARE: strcmp, strncmp


void clear()
{
	write(STDOUT_FILENO, "\033[H\033[2J\033[3J", 11); 
	//esegue clear "\033[H" si muove a HOME , "\033[2J" pulisce 
	//l'area attuale "\033[3J" pulisce anche la history
}

int main() 
{
    char* input;
	int size = 100;
	char *pwd;

	clear(); //pulisce all'avvio
    while (1) {
        input = readline("Minishell> "); //stampa e aspetta un input

        if (strcmp(input, "exit") == 0)
            break;
		else if(strcmp(input, "clear") == 0)
			clear();
		else if(strncmp(input, "cd", 2))
		{
			if(chdir(input + 2) != 0)// chdir controlla che la path sia giusta e esegue il processo per entrarci
				perror("Path invalida.\n");
			else
				printf("entrato con successo in: %s", input+3);



			//CONTROLLARE NON CORRETTO!!


		}
		else if(strcmp(input, "pwd"))
		{
			pwd = malloc(sizeof(char) * size);
			getcwd(pwd, size); // prendi path e salvalo in "pwd";
			printf("%s\n", pwd);



			//CONTROLLARE NON CORRETTO!!


		}
		
        add_history(input); // aggiunge alla storia da solo! non serve la struct
        free(input);
    }

    return 0;
}