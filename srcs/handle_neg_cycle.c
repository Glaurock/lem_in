/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_neg_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 10:04:28 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 15:25:59 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	adjust_negative_cycle(t_graph *graph)
{
	int		current;
	int		i;
	t_edge	*edge;
	t_edge	*reverse_edge;

	current = graph->end;
	i = -1;
	while (++i < graph->nb_sommets)
	{
		edge = give_edge(graph, current, graph->tab[PATH][current]);
		reverse_edge = give_edge(graph, graph->tab[PATH][current], current);
		if (!edge->is_full && !reverse_edge->is_full)
			edge->is_full = 1;
		else if (reverse_edge->is_full)
			reverse_edge->is_full = 0;
		current = graph->tab[PATH][current];
		if (current == graph->end)
			break ;
	}
}

int		node_loop(t_graph *graph, int code)
{
	t_node *node;
	t_edge *edge;

	node = graph->head;
	while (node)
	{
		edge = node->edges_l;
		while (edge)
		{
			if (!edge->wrong_way && graph->tab[WEIGHT][node->number]
			+ edge->w < graph->tab[WEIGHT][edge->links_to->number])
			{
				graph->tab[WEIGHT][edge->links_to->number] =
				graph->tab[WEIGHT][node->number] + edge->w;
				graph->tab[PATH][edge->links_to->number] = node->number;
				if (code)
					return (1);
			}
			edge = edge->next;
		}
		node = node->next;
	}
	return (0);
}

int		find_negative_path(t_graph *graph)
{
	int		i;

	ft_memset(graph->tab[WEIGHT], INF, sizeof(int) * graph->nb_sommets);
	ft_memset(graph->tab[PATH], -1, sizeof(int) * graph->nb_sommets);
	graph->tab[WEIGHT][graph->end] = 0;
	i = -1;
	while (++i < graph->nb_sommets)
		node_loop(graph, 0);
	return (node_loop(graph, 1));
}
