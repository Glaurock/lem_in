/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:12:50 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/29 17:15:11 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_graphics.h"

void	push_list(t_list_point **head, int x, int y, char *name)
{
	t_list_point	*new;
	t_point			*point;

	new = (t_list_point*)ft_memalloc(sizeof(t_list_point));
	if (!new)
		return ;
	point = (t_point*)ft_memalloc(sizeof(t_point));
	point->x = x;
	point->y = y;
	new->point = point;
	new->name = ft_strdup(name);
	new->next = *head;
	*head = new;
}

void	get_input(t_list_point **list, char **line)
{
	char			**splitted;

	get_next_line(0, line);
	ft_memdel((void**)line);
	while (get_next_line(0, line) > 0)
	{
//		ft_printf("%s\n", line);
		if (strchr(*line, '-'))
			break ;
		if (*line[0] != '#')
		{
			splitted = ft_strsplit(*line, ' ');
			push_list(list, ft_atoi(splitted[1]), ft_atoi(splitted[2]), splitted[0]);
			free_splitted(splitted);
		}
		ft_memdel((void**)line);
	}
}

