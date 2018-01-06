/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_neg_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 10:04:28 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 13:41:35 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	adjust_negative_cycle(t_graph *graph)
{
	int current;
	int i;
	t_edge *edge;
	t_edge *reverse_edge;

	current = graph->end;
	i = -1;
	while (++i < graph->nb_sommets)
	{
		edge = give_edge(graph, current, graph->tab[PATH][current]);
		reverse_edge = give_edge(graph, graph->tab[PATH][current], current);
		//ft_dprintf(2, "edge: %d\n", edge->wrong_way);
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

	//relax edges
	//ft_memset(graph->tab[SEEN], false, sizeof(int) * graph->nb_sommets);
	node = graph->head;
	//graph->tab[SEEN][node->number] = true;
	while (node)
	{
		edge = node->edges_l;
		while (edge)
		{
			//ft_dprintf(2, "edge from: (%d) to (%d) is %s \n", node->number, edge->links_to->number, edge->is_full ? "full" : "empty");
			//ft_dprintf(2, "weight node: %d, weight links to : %d, w: %d\n", graph->tab[WEIGHT][node->number], graph->tab[WEIGHT][edge->links_to->number], edge->w);
			if (!edge->wrong_way && graph->tab[WEIGHT][node->number] + edge->w < graph->tab[WEIGHT][edge->links_to->number])// && graph->tab[SEEN][edge->links_to->number] == false)
			{
				//ft_dprintf(2, "Dans le if\n\n");
				graph->tab[WEIGHT][edge->links_to->number] = graph->tab[WEIGHT][node->number] + edge->w;
				graph->tab[PATH][edge->links_to->number] = node->number;
				//print_weight(graph->tab, graph->nb_sommets);
				if (code)
				{
					ft_dprintf(2, "\nIl existe un cycle absorbant\n");
					return (1);
				}
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
	//print_weight(graph->tab, graph->nb_sommets);

	i = -1;
	while (++i < graph->nb_sommets)
		node_loop(graph, 0);
	
	//print_weight(graph->tab, graph->nb_sommets);

	//last iteration
	//print_weight(graph->tab, graph->nb_sommets);
	return (node_loop(graph, 1));
}
