/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:14:43 by shhuang           #+#    #+#             */
/*   Updated: 2023/09/30 18:44:14 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// IMPLEMENTARE: strcmp, strncmp
#include "minishell.h"

void clear()
{
	write(STDOUT_FILENO, "\033[H\033[2J\033[3J", 11); 
	//esegue clear "\033[H" si muove a HOME , "\033[2J" pulisce 
	//l'area attuale "\033[3J" pulisce anche la history
}

void print_env(char **env)
{
	for (int i = 0; env[i]; i++)
		printf("%s ", env[i]);
}

void print_env_var(char **env, char *var)
{
	for (int i = 0; env[i]; i++)
	{
		if (!strncmp(env[i], var, strlen(var)))
			printf("%s\n", env[i]);
	}
}

int main(int argc, char **argv, char **env) 
{
    char* input;
	char *pwd;

	(void)argc;
	(void)argv;
	clear(); //pulisce all'avvio
    while (1) {
		// print_env(env);
        input = readline("Minishell> "); //stampa e aspetta un input
        if (ft_strncmp(input, "exit", 5) == 0)
            exit(0);
		else if(ft_strncmp(input, "clear", 6) == 0)
			clear();
		else if(ft_strncmp(input, "cd", 3) == 0)
		{
			if(chdir(&input[3]) == 0)// chdir controlla che la path sia giusta e esegue il processo per entrarci
				;
			else
				printf("cd: %s")

			//CONTROLLARE NON CORRETTO!!


		}
		else if(ft_strcmp(input, "pwd", 4) == 0)
		{
			pwd = malloc(sizeof(char) * PATH_MAX);
			getcwd(pwd, PATH_MAX); // prendi path e salvalo in "pwd";
			printf("%s\n", pwd);

			print_env_var(env, "PWD");
			//CONTROLLARE NON CORRETTO!!


		}
		else
		{
			;
		}
		
        add_history(input); // aggiunge alla storia da solo! non serve la struct
        free(input);
    }

    return 0;
}