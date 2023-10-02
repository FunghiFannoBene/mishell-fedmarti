#include "minishell.h"

// int checkflag(char *c)
// {
// 	if(c == '"')
// 	{
// 		return(1);
// 	}
// 	else if(c == '\'')
// 	{
// 		return(2);
// 	}
// 	else
// 		return(3);
// }

int odd_virgolette(char *s)
{
    int i = 0;
    int count_single;
    count_single = 0;
    int count_double;
    count_double = 0;
    while(s[i])
    {
        if(s[i] == '\\' && s[i+1] == '\\' || (s[i] == '\\' && (s[i+1] == '\'' || s[i+1] == '"')))
            i+=2;
        else if(s[i] == '\'')
        {
            i++;
            count_single++;
            while(s[i] && s[i] != '\'')
            {
                i++;
                if(s[i] == '\'' && s[i-1] == '\\')
                  i++;
            }
            if(s[i] == '\0')
              break;
            else
              count_single++;
            i++;
        }
        else if(s[i] == '"')
        {
            i++;
            count_double++;
            while(s[i] && s[i] != '"')
            {
                i++;
                if(s[i] == '"' && s[i-1] == '\\')
                  i++;
            }
            if(s[i] == '\0')
              break;
            else
              count_double++;
            i++;
        }
        else
            i++;
    }
    if((count_double % 2) == 0 && (count_single % 2) == 0)
        return(1);
    return(0);
    //Trova se la stringa contiene dispari ' o " senza contare quelle precedute da // (ma non precedute da /// 3 o +) UN casino
}




int calculate_string_size(char *s, int i) //t_list da aggiungere
{ //echo = 4 cat = 3 etc numero dei caratteri
    char flag = 0;
    int count = 0;

    if(s[i] == ' ')
    {
		while(s[i] == ' ')
		i++;
    }
    else
      return(-1);
    while(s[i])
    {
        if(s[i] == '\'')
            flag = '\'';
        else if(s[i] == '"')
            flag = '"';
        if(flag != 0)
            i++;
        if(flag == s[i])
        {
          i++;
          flag = 0;
          continue;
        }
        while(s[i])
        {
			printf("%c", s[i]);
			printf("|");
			if((flag == 0 || flag == '"' )&& s[i] == '\\' && s[i+1] == '\\' )
			{
				i+=2;
				count++;
				continue;
			}
			if(flag == 0 && s[i] == '\\' && (s[i+1] == '\'' || s[i+1] == '"'))
			{
				count++;
				i+=2;
				continue;
			}
			if(s[i] == '\\' && s[i+1] == '"')
            {
                count++;
                i+=2;
                continue;
            }
            if(s[i] == flag)
            {
                i++;
				if(s[i] == '\0')
                  return count;
                flag = 0; //ho trovato la chiusura ma la stringa potrebbe continuare ancora
                break;
            }
            else if(flag == 0 && s[i] == '|')
            {
                i++;
                return(count); //ritorno conta se trova un simbolo significativo non incluso tra virgolette
            }
            if((flag == 0 || flag == '"') && s[i] == '$')
                count += 0; //Non funzionale finche non c'è env; Si attiva solo se $ è tra le "$" o senza nulla.
            if(flag == 0 && s[i] == ' ') //se non sono dentro le virgolette e trovo uno spazio skippo tutto. e continuo senza aggiungere i++;
            {
                while(s[i] && s[i] == ' ')
                    i++;
				if(s[i] == '\0')
					return(count);
                count++;
                break;
            }
			if(flag == 0 && (s[i] == '\'' || s[i] == '"'))
              break;
            count++;    //count arg size;
            i++;
        }
        
    }
    return(count);
}


void insert_string(char*s, char **str, int* x)
{
	int i = *x;
    char flag = 0;
    int count = 0;
    if(s[i] == ' ')
    {
    	while(s[i] == ' ')
      		i++;
    }
     while(s[i])
    {
        if(s[i] == '\'')
            flag = '\'';
        else if(s[i] == '"') 
        {
            flag = '"';
        }
        if(flag != 0)
            i++;
        if(flag == s[i])
        {
          i++;
          flag = 0;
          continue;
        }
        while(s[i])
        {
            if((flag == 0 || flag == '"') && s[i] == '\\' && s[i+1] == '\\' )
            {
                (*str)[count] = s[i];
                i+=2;
                count++;
                continue;
            }
            if(flag == 0 && s[i] == '\\' && (s[i+1] == '\'' || s[i+1] == '"'))
            {
                (*str)[count] = s[i+1];
                count++;
                i+=2;
                continue;
            }
            if(s[i] == '\\' && s[i+1] == '"')
            {
                (*str)[count] = s[i+1];
                count++;
                i+=2;
                continue;
            }
            if(s[i] == flag)
            {
                i++;
                if(s[i] == '\0')
                {
					*x = i;
                  (*str)[count] = '\0';
                  return;
                }
                flag = 0; 
                break;
            }
            else if(flag == 0 && s[i] == '|')
            {
                i++;
				*x = i;
                (*str)[count] = '\0';
                return; 
            }
            if((flag == 0 || flag == '"') && s[i] == '$')
                count += 0; 
            if(flag == 0 && s[i] == ' ') 
            {
                (*str)[count] = s[i];
                while(s[i] && s[i] == ' ')
                    i++;
                count++;
                break;
            }
            if(flag == 0 && (s[i] == '\'' || s[i] == '"'))
              break;
            (*str)[count] = s[i];
            count++;
            i++;
        }
    }
	*x = i;
	printf("ritorno\n");
    (*str)[count] = '\0';
}

int execute(char **args)
{
	pid_t pid;
	 // Arguments to pass to 'cat'
    
    pid = fork();  // Create a child process
    
    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        execve("/usr/bin/cat", args, NULL); // Execute the 'cat' command

        // If execve() fails:
        perror("execve failed");
        _exit(1); // It's generally better to use _exit() than exit() in this context
    } else {
        // Parent process
        int status;
        wait(&status);  // Wait for the child to finish
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            // Check if child terminated normally and if its exit status is non-zero
            fprintf(stderr, "child exited with status: %d\n", WEXITSTATUS(status));
        }
    }
}


void search_command(char *input, int *i, t_indice *command_list)
{
    int x = 0;
    int start;

    while (input[*i] && input[*i] == ' ')
        (*i)++;
    start = *i;
    while (input[start + x] && input[start + x] != ' ')
        x++;
    command_list->command_name = malloc(sizeof(char) * (x + 1));
    if (!command_list->command_name)
        return;
    x = 0;
    while (input[*i] && input[*i] != ' ')
        command_list->command_name[x++] = input[(*i)++];
    command_list->command_name[x] = '\0';
	printf("\n\n%s e index si ferma a: %d\n\n", command_list->command_name, *i);
}



t_indice* create_commands_list(char *input) {
    t_indice *command_list = NULL;
    t_indice *head = NULL;
    t_indice *prev = NULL;
    int index = 0;

    while (input[index]) {
        command_list = malloc(sizeof(t_indice));
        if (!command_list) {
            return NULL;
        }
        search_command(input, &index, command_list);
        command_list->next = NULL;

        int size = calculate_string_size(input, index);
        if (size == -1) 
		{
			//freelist
            printf("\n\nLista non creata: err-1;\n\n");
            free(input);
            return NULL;
        }
        if (!head)
            head = command_list;
        else if (prev)
            prev->next = command_list;
        prev = command_list;
        command_list->stringa = calloc(size + 1, sizeof(char));
        insert_string(input, &command_list->stringa, &index);
		printf("\n\n|%c|\n\n", input[index]);
		if(input[index] == '\0')
		{
			prev->next = NULL;
			free(input);
			return(head);
		}
    }
    return head;
}

int main() {
	while(1)
	{

		//stringhe non funzionanti : 
		//echo "c"i'a\\\'o\'\'\'\'
		//output: cia\\\o''''        Se inizia con slash la virgoletta non ha significato!!
		//per testare quello di sopra: char input[50] = "echo \"c\"i'a\\\\\\'o\\'\\'\\'\\'";
		//echo "c"i'a\\\'o  
		//output == cia\\\o slash non deve avere significato se dentro virgolette.
		//echo 'It'\''s a "mixed" bag: '\''$var'\''!'
		//output: It's a "mixed" bag: '$var'!
		//ERRORI ANCORA da fix
		//echo "This is a \"nested\" quote."
		//echo "This is \"complex\" with some 'mixed' quotes. 'And within these quotes we escape.'" "Then we add \"more\" complexity." 'Backslashes: \\\\ and then \\\\\\ more.'
		//echo "Hello, \"world\"!" 'It'\''s a beautiful day.' "Isn't it?" 'Look at these backslashes: \\\\' "More \\\\"

		//Fondere readline
		// PROBLEMA!!!!!! echo "chat\" ciao \" mondo 22\\"    TERMINALE: chat" ciao " mondo 22\    PROGRAMMA: chat ciao  mondo 22\
		

		//FONDERE RIMOZIONE \ con CREA OUTPUT UGUALE A ECHO ETC.. //readline va tenuto
		char *input = readline("Stringa: ");
		printf("\nReadline =%s\n", input);
		// char **args = calloc(sizeof(char*) , 3);

		// args[0] = strdup("cat");
		// if (!args[0]) 
		// {
    	// 	perror("Memory allocation failed");
    	// 	exit(1);
		// }
		// args[2] = NULL;
		
		// char* nuovo_input = calloc((size_readline(input)+1), sizeof(char));
		// nuovo_input = adapt_readline(input, nuovo_input);
		// free(input);


		t_indice *command_list;
		command_list = create_commands_list(input);
		while(command_list != NULL)
		{
			printf("Lista: Comando: %s Content: %s\n", command_list->command_name, command_list->stringa);
			command_list=command_list->next;
		}

		// args[1] = s;
		// if(strncmp("cat", input, 3) == 0)//cat impostare i a 3
		// 	execute(args); 
		// free(input);
	}	
}


// int main()
// {
//   char *s = calloc( sizeof(char) , 19 );
//   char x[50] = "echo \"He's a \"good\" guy.\"";
//     insert_string(x, &s);
//      printf("%s", s);
// }

// char *editstring(char *s, t_list*env)
// {
// 	int i = 4; // command size
// 	int flag;
// 	char *string;
// 	if(s[i] == '\0') //nel caso ci sia echo
// 	{
// 		string = calloc(1, sizeof(char));
// 		return(string);
// 	}
// 	if(s[i] != ' ') //nel caso ci sia echoabc
// 	{
// 		perror("echo not valid.\n");
// 		return(NULL);
// 	}
// 	while(s[i] && s[i] == ' ')
// 		i++;
// 	if(!s[i]) //nel caso di solo spazi
// 	{
// 		string = calloc(1, sizeof(char));
// 		return(string);
// 	}

// 	//END CHECKS

// 	//if " o ' priority
// 	calculate_string_size(s+i);

// 	while(s[i])
// 	{
// 		if(flag == 0)
// 		{
			
// 			checkflag(s[i]);
// 		}
// 		else if(flag == 1)
// 		{
// 			i += print_till(checkclosing(s+i,'"'));
// 			while(s[i] && s[i] == ' ')
// 				i++;
// 			flag = 0;
// 		}
// 		else if(flag == 2)
// 		{
// 			i += print_till(checkclosing(s+i, '\''));
// 			while(s[i] && s[i] == ' ')
// 				i++;
// 			flag = 0;
// 		}

// 	}
	
// }

// void echo(char *s)
// {
	
// }


// int main(int argc, char **argv, char**env)
// {
// 	int i=0;

// }