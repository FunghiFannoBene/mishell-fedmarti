#include "minishell.h"

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
            flag = '\''; //inserisci tutto fino '
        else if(s[i] == '"') //inserisci tutto fino a "
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
            if(s[i] == flag)
            {
                i++;
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
                while(s[i] && s[i] == ' ')
                    i++;
                *str[count] = s[i];
                count++;
                break;
            }
            (*str)[count] = s[i];
            count++;    //count arg size;
            i++;
        }
    }
    (*str)[count] = '\0';
    return;
}


int main()
{
  char *s = calloc(size + 1, sizeof(char));
  char x[50] = "echo \"He's a \"good\" guy.\"";
    insert_string(x, &s);
     printf("%s", s);
}