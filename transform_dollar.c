/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 20:19:51 by shhuang           #+#    #+#             */
/*   Updated: 2023/10/25 22:41:35 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipeline.h"

int check_invalid(char c, char* invalid)
{
	int i = 0;
	while(invalid[i])
	{
		if(invalid[i] == c)
			return(1);
		i++;
	}
	return(0);
}

int checksymbol(char *s)
{
	if (s == NULL)
		return (0);
	int i = 0;
	while(s[i] != '\0')
	{
		if(check_invalid(s[i], NOT_VALID) == 1)
			return(i+1);
		i++;
	}
	return(i);
}

int checksymbol2(char *s)
{
	if (s == NULL)
		return (0);
	int i = 0;
	while(s[i] != '\0')
	{
		if(check_invalid(s[i], NOT_VALID) == 1)
			return(i+1);
		i++;
	}
	return(i+1);
}

char *add_slashes(char *tmp)
{
	if(!tmp)
		return(NULL);
	int i = 0;
	int count = 0;
	int x = 0;
	char *str;
	while(tmp[i])
	{
		if(tmp[i] == '\'' || tmp[i] == '"')
			count++;
		i++;
	}
	i=0;
	if(count == 0)
		return tmp;
	str = malloc(sizeof(char) * (ft_strlen(tmp) + count +1));
	while(tmp[x])
	{
		if(tmp[x] == '\'' || tmp[x] == '"')
		{
			str[i] = '\\';
			i++;
		}
		str[i] = tmp[x];
		x++;
		i++;
	}
	str[i] = '\0';
	free(tmp);
	return(str);
}

char *ft_strndup(const char *s, size_t n)
{
    char *result;
    size_t len = n;

    result = (char *)malloc(len + 1);
    if (!result)
        return NULL;

    result[len] = '\0';
    return (char *)ft_memcpy(result, s, len);
}



char *replace_for_new_str(char* s,char* tmp, int i, int size)
{
	int env_len;
	// char *str;
	char *result;
	char *start;

	(void)size;
	env_len = checksymbol2(s+i+1);
	while(s[i])
	{
		if(s[i] == '$')
		{
			start = ft_strndup(s, i);
			if(tmp == NULL)
				result = ft_multistrjoin((char *[]) {start, s+i+env_len, NULL});
			else
				result = ft_multistrjoin((char *[]) {start, "'", tmp, "'", s+i+env_len, NULL});
			if(tmp)
			{
				free(tmp);
				tmp = NULL;
			}
			free(start);
			free(s);
			s = NULL;
			return(result);
		}
		i++;
	}
	return(s);
}


char *transform_for_dollar(char *s, t_data* data)
{
	char *tmp;
	int i = 0;
	t_var *list;
	int env_len;
	int save;
	int size;
	int slash_count;
	int start;
	int flag = 0;
	size = 0;
	
	slash_count = 0;
	while(s[i] != '\0')
	{
		tmp = NULL;
		if(s[i] == '\\')
		{
			while(s[i] == '\\')
			{
				slash_count++;
				i++;
			}
		}
		else
			slash_count = 0;
		if(s[i] == '\'')
			flag = 1;
		while(s[i] && flag == 1)
		{
			i++;
			if(s[i] == '\'')
				flag = 0;
		}
		if(s[i] == '\0')
			return(s);
		start = i;
		if(s[i] == '$' && slash_count % 2 == 0 && (env_len = checksymbol(s+i+1)))
		{
			save = s[i+env_len];
			s[i+env_len] = '\0';
			list = search_variable_tvar(s+i, data);
			s[i+env_len] = save;
			if(list != NULL)
			{
				tmp = ft_strdup(list->value);
				tmp = add_slashes(tmp);
				size = ft_strlen(tmp);
				i+=size+1;
			}
			s = replace_for_new_str(s, tmp, start, size);
		}
		i++;
	}
	return(s);
}
