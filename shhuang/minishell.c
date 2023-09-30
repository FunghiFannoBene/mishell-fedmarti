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
	//Trova se la stringa contiene dispari ' o " senza contare quelle precedute da // (ma non precedute da /// 3 o +) UN casino
	return(1);
}



int calculate_string_size(char *s) //t_list da aggiungere
{
    int i = 4;
    char flag = 0;
    int count = 0;

	if(!odd_virgolette(s+1))
	{
		return(-1);
	}

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
        { //inserisci tutto fino '
            flag = '\'';
        }
        else if(s[i] == '"') //inserisci tutto fino a "
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
            if(s[i] == flag)
            {
                i++;
				if(s[i] == '\0')
                  return count;
                flag = 0; //ho trovato la chiusura ma la stringa potrebbe continuare ancora
                break;
            }
            else if(flag == 0 && (s[i] == '<' || s[i] == '>' || s[i] == '|'))
            {
                i++;
                return(count); //ritorno conta se trova un simbolo significativo non incluso tra virgolette
            }
            if((flag == 0 || flag == '"') && s[i] == '$')
                count += '$'; //Non funzionale finche non c'è env; Si attiva solo se $ è tra le "$" o senza nulla.
            if(flag == 0 && s[i] == ' ') //se non sono dentro le virgolette e trovo uno spazio skippo tutto. e continuo senza aggiungere i++;
            {
                while(s[i] && s[i] == ' ')
                    i++;
				if(s[i] == '\0')
					return(count);
                count++;
                break;
            }
			if(flag == 0 && s[i] == '\'' || s[i] == '"')
              break;
            count++;    //count arg size;
            i++;
        }
        
    }
    return(count);
}


void insert_string(char*s, char **str) //t_list da aggiungere
{
    int i = 4;
    char flag = 0;
    int count = 0;
    if(s[i] == ' ')
    {
    while(s[i] == ' ')
      i++;
    }
    else
      return;
    while(s[i])
    {
        if(s[i] == '\'')
        { //inserisci tutto fino '
            flag = '\'';
        }
        else if(s[i] == '"') //inserisci tutto fino a "
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
            if(s[i] == flag)
            {
                i++;
                if(s[i] == '\0')
                {
                  (*str)[count] = '\0';
                  return;
                }
                flag = 0; //ho trovato la chiusura ma la stringa potrebbe continuare ancora
                break;
            }
            else if(flag == 0 && (s[i] == '<' || s[i] == '>' || s[i] == '|'))
            {
                i++;
                (*str)[count] = '\0';
                return; //ritorno conta se trova un simbolo significativo non incluso tra virgolette
            }
            if((flag == 0 || flag == '"') && s[i] == '$')
                count += '$'; //Non funzionale finche non c'è env; Si attiva solo se $ è tra le "$" o senza nulla.
            if(flag == 0 && s[i] == ' ') //se non sono dentro le virgolette e trovo uno spazio skippo tutto. e continuo senza aggiungere i++;
            {
                (*str)[count] = s[i];
                while(s[i] && s[i] == ' ')
                    i++;
                count++;
                break;
            }
            if(flag == 0 && s[i] == '\'' || s[i] == '"')
              break;
            (*str)[count] = s[i];
            count++;    //count arg size;
            i++;
        }
    }
    (*str)[count] = '\0';
    return;
}


int size_readline(char *input)
{
	int i=0;
	int count = 0;
	while(input[i])
	{
		if(input[i+1] == '\\' && input[i] == '\\' )
		{
			count++;
			i+=2;
		}
		else if(input[i] == '\\')
			i++;
		else
		{
			i++;
			count++;
		}
	}
	return(count);
}

char* adapt_readline(char *input, char* nuovo_input)
{
	int i=0;
	int count = 0;
	while(input[i])
	{
		if(input[i+1] == '\\' && input[i] == '\\' )
		{
			nuovo_input[count] = input[i]; 
			count++;
			i+=2;
		}
		else if(input[i] == '\\')
			i++;
		else
		{
			nuovo_input[count] = input[i];
			i++;
			count++;
		}
	}
	nuovo_input[count] = '\0';
	return(nuovo_input);
}



int main() {
	while(1)
	{
		//Fondere readline
		// PROBLEMA!!!!!! echo "chat\" ciao \" mondo 22\\"    TERMINALE: chat" ciao " mondo 22\    PROGRAMMA: chat ciao  mondo 22\
		

		//FONDERE RIMOZIONE \ con CREA OUTPUT UGUALE A ECHO ETC.. //readline va tenuto
		char *input = readline("Stringa: ");
		printf("\nReadline =%s\n", input);

		char* nuovo_input = calloc((size_readline(input)+1), sizeof(char));
		nuovo_input = adapt_readline(input, nuovo_input);
		free(input);
		printf("\nNuovo input =%s\n", nuovo_input);
		int size = calculate_string_size(nuovo_input);
		char *s = calloc(size + 1, sizeof(char));
		insert_string(nuovo_input, &s);
		free(nuovo_input);
		printf("\nsono il risultato:\n%s\n", s);
		free(s);
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