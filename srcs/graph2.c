/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 15:21:32 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/22 12:42:01 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node				*give_node_name(t_graph *graph, char *name)
{
	t_node *node;

	node = graph->head;
	while (node)
	{
		if (ft_strcmp(node->name, name) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

t_node				*give_node(t_graph *graph, int number)
{
	t_node *node;

	node = graph->head;
	while (node)
	{
		if (node->number == number)
			return (node);
		node = node->next;
	}
	return (NULL);
}

t_edge				*give_edge(t_graph *graph, int son, int parent)
{
	t_edge *edge;
	t_node *node;

	node = graph->tab_nodes[parent];
	edge = node->edges_l;
	while (edge)
	{
		if (edge->links_to->number == son)
			return (edge);
		edge = edge->next;
	}
	return (NULL);
}
