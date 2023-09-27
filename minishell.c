/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <shhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:14:43 by shhuang           #+#    #+#             */
/*   Updated: 2023/09/27 19:02:55 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int main(int argc, char**argv, char**envp)
{	

	t_dblist *new;
	new = NULL;

	new = malloc(sizeof(t_dblist));
	new->next = NULL;
	int i=0;
	while(envp[i])
	{
		printf("%s\n", envp[i++]);
	}
}