/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 11:30:33 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/20 11:29:31 by jpriou           ###   ########.fr       */
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

void	push_edges(t_list_edges **head, char *node1, char *node2)
{
	t_list_edges	*new;

	new = (t_list_edges*)ft_memalloc(sizeof(t_list_edges));
	if (!new)
		return ;
	new->node1 = ft_strdup(node1);
	new->node2 = ft_strdup(node2);
	new->next = *head;
	*head = new;
}

t_point	*get_point_in_list(t_env *env, char *name)
{
	t_list_point *list;

	list = env->head_points;
	while (list)
	{
		if (ft_strcmp(list->name, name) == 0)
			return (list->point);
		list = list->next;
	}
	return (NULL);
}
