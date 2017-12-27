/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 21:13:06 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/27 16:07:08 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_path(t_node *path)
{
	ft_dprintf(2, "Path : ");
	while (path)
	{
		ft_dprintf(2, "(%d) --> ", path->number);
		path = path->next;
	}
	ft_dprintf(2, "END\n");
}

void		ft_reverse_path(t_node **begin_list)
{
	t_node *save_next;
	t_node *new;
	t_node *copy;

	if (begin_list)
	{
		new = 0;
		copy = *begin_list;
		while (copy)
		{
			save_next = copy->next;
			copy->next = new;
			new = copy;
			copy = save_next;
		}
		*begin_list = new;
	}
}

int			ft_path_size(t_node *node)
{
	int i;

	i = 0;
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}

void		free_path(t_node *path)
{
	t_node	*tmp;

	while (path)
	{
		tmp = path;
		path = path->next;
		free(tmp);
	}
}

void		push_path(t_node **head, t_node *path) // FREE
{
	t_node *copy;

	mallcheck(copy = (t_node*)malloc(sizeof(t_node)));
	//ft_memcpy(copy, path, sizeof(t_node));
	copy->number = path->number;
	copy->next = *head;
	*head = copy;
}
