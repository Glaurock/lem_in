/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:18:48 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 15:23:56 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node				*create_node(int number, char *name)
{
	t_node		*new;

	mallcheck(new = (t_node*)ft_memalloc(sizeof(t_node)));
	new->number = number;
	new->is_free = 1;
	new->name = ft_strdup(name);
	return (new);
}

void				push_end(t_graph *graph, t_node *node)
{
	t_node *current;

	if (!graph)
		return ;
	if (!graph->head)
		graph->head = node;
	else
	{
		current = graph->head;
		while (current->next)
			current = current->next;
		current->next = node;
	}
}

t_edge				*new_edge(t_node *links_to)
{
	t_edge		*edge;

	mallcheck(edge = (t_edge*)ft_memalloc(sizeof(t_edge)));
	edge->links_to = links_to;
	return (edge);
}

void				add_edge(t_node *n1, t_node *n2)
{
	t_edge		*edge;

	if (!n1 || !n2)
		die("Can't add edge");
	edge = new_edge(n2);
	edge->next = n1->edges_l;
	n1->edges_l = edge;
	edge = new_edge(n1);
	edge->next = n2->edges_l;
	n2->edges_l = edge;
}

void				del_graph(t_graph *graph)
{
	t_node		*node;
	t_node		*tmp;
	t_edge		*edge;
	t_edge		*tmp_edge;

	if (!graph)
		return ;
	node = graph->head;
	while (node)
	{
		tmp = node;
		edge = node->edges_l;
		while (edge)
		{
			tmp_edge = edge;
			edge = edge->next;
			free(tmp_edge);
		}
		node = node->next;
		free(tmp->name);
		free(tmp);
	}
	ft_memdel((void**)&graph);
}
