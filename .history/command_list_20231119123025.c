/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:50:06 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/19 12:30:25 by shhuang          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "short_code.h"

t_pnode	*create_command_list(char *s)
{
	t_command	c;

	if (init_command(&c, s) == -1)
		return (NULL);
	while (1)
	{
		if (check_continuation(s, &c))
			break ;
		c.x = evaluate_next_struct(&c, s);
		if (c.x == -2)
			continue ;
		else if (c.x == 0)
			return (NULL);
		else if (c.x == 1)
			return (c.structure_head);
		command_to_structure(&c);
		structure_linking(&c);
		if (c.command_record == -1 || c.type == -2)
			break ;
	}
	return (c.structure_head);
}
faafsfasa