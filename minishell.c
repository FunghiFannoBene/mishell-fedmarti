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

void clear()
{
	printf("Minishell: ");	
}

int main(int argc, char**argv, char**envp)
{	

	t_dblist *new;
	(void)argv;
	new = malloc(sizeof(t_dblist));
	new->next = NULL;
	int i=0;
	clear();
	while(1)
	{
		
	}
}