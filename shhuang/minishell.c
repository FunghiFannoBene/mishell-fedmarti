#include "minishell.h"

int checkflag(char *c)
{
	if(c == '"')
	{
		return(1);
	}
	else if(c == '\'')
	{
		return(2);
	}
	else
		return(3);
}


int calculate_string_size(char *s, t_list*env)
{
	int i = 0;
	int flag = 0;
	while(s[i])
	{
		if(s[i] == '\'') //inserisci tutto fino '
			flag = 1;
		else if(s[i] == '"') //inserisci tutto fino a "
			flag = 2;
		else
			flag = 3; //normal echo
		while(s[i])
		{
			if(flag == 1)
			{

			}
		}
	}
}


char *editstring(char *s, t_list*env)
{
	int i = 4;
	int flag;
	char *string;
	if(s[i] == '\0') //nel caso ci sia echo
	{
		string = calloc(1, sizeof(char));
		return(string);
	}
	if(s[i] != ' ') //nel caso ci sia echoabc
	{
		perror("echo not valid.\n");
		return(NULL);
	}
	while(s[i] && s[i] == ' ')
		i++;
	if(!s[i]) //nel caso di solo spazi
	{
		string = calloc(1, sizeof(char));
		return(string);
	}

	//END CHECKS

	//if " o ' priority
	calculate_string_size(s+i);

	while(s[i])
	{
		if(flag == 0)
		{
			
			checkflag(s[i]);
		}
		else if(flag == 1)
		{
			i += print_till(checkclosing(s+i,'"'));
			while(s[i] && s[i] == ' ')
				i++;
			flag = 0;
		}
		else if(flag == 2)
		{
			i += print_till(checkclosing(s+i, '\''));
			while(s[i] && s[i] == ' ')
				i++;
			flag = 0;
		}

	}
	
}

void echo(char *s)
{
	
}


int main(int argc, char **argv, char**env)
{
	int i=0;
	echo(editstring(char *s, t_list*env));
}