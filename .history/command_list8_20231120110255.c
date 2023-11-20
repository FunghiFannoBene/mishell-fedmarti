/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <dsheng1993@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:45:39 by shhuang           #+#    #+#             */
/*   Updated: 2023/11/20 11:02:55 by shhuang          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "short_code.h"

void	assign_structure(t_command *c)
{
	c->structure->args = NULL;
	c->structure->output = NULL;
	if (c->structure_actual == NULL)
	{
		c->structure_head = c->structure;
		c->structure_actual = c->structure_head;
	}
	else
	{
		c->structure_actual->output = c->structure;
		c->structure_actual = c->structure_actual->output;
	}
}

int	is_void(t_command *c)
{
	if (c->structure->type == Null && !c->structure_head)
	{
		free(c->structure);
		return (1);
	}
	return (0);
}

int	evaluate_next_struct(t_command *c, char *s)
{
	c->type = search_command(s, &c->i, &c->command, c->structure);
	if (c->type == 0)
		c->command_record = size_of_command(s, &c->i, &c->command,
				c->structure);
	else if (c->type == -1)
	{
		free(c->structure);
		free_t_pnode_list(c->structure_head);
		return (0);
	}
	else if (c->type == -3)
	{
		if (is_void(c))
			return (0);
		free(c->structure);
		return (1);
	}
	else if (c->type == -4)
	{
		assign_structure(c);
		return (-2);
	}
	return (3);
}

void	command_to_structure(t_command *c)
{
	c->head = c->command;
	if (c->structure_head == NULL)
		c->structure_head = c->structure;
	c->x = 0;
	c->command = c->head;
	while (c->command)
	{
		c->x++;
		c->command = c->command->next;
	}
	c->structure->args = ft_calloc(sizeof(char *) , (size_t)(c->x + 1));
	c->structure->input_fd = 0;
	c->structure->output_fd = 1;
	c->x = 0;
	while (c->head)
	{
		if(c->head && c->head->status == 1)
		{
			while(c->head && c->head->status == 1)
			{
				if(c->structure->args[c->x] == NULL)
					c->structure->args[c->x] = ft_strdup("");
				if(c->head && c->head->str)
				{
					c->structure->args[c->x] = ft_strjoin(c->structure->args[c->x], c->head->str);
				}
				free(c->head->str);
				c->temp = c->head;
				c->head = c->head->next;
				free(c->temp);
			}
			if(c->head && c->head->str)
			{
				c->structure->args[c->x] = ft_strjoin(c->structure->args[c->x], c->head->str);
			}
			free(c->head->str);
			c->temp = c->head;
			c->head = c->head->next;
			free(c->temp);
		}
		else
		{
			c->structure->args[c->x] = ft_strdup(c->head->str);
			free(c->head->str);
			c->temp = c->head;
			c->head = c->head->next;
			free(c->temp);
		}
		c->x++;
	}
	c->structure->args[c->x] = NULL;
	c->structure->output = NULL;
}

void	structure_linking(t_command *c)
{
	if (c->structure_actual == NULL)
		c->structure_actual = c->structure_head;
	else
	{
		c->structure_actual->output = c->structure;
		c->structure_actual = c->structure_actual->output;
	}
}
