/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_algo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:16:05 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 15:26:26 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			calc_nb_lap(t_graph *graph, int code)
{
	int		ret;
	int		total_path_dist;
	int		nb_path;
	t_list	*list;

	ret = 0;
	total_path_dist = 0;
	nb_path = 0;
	list = code ? graph->list_paths : graph->list_tmp;
	while (list)
	{
		total_path_dist += count_path_size((int*)list->content,
		graph->nb_sommets, graph->end);
		list = list->next;
		nb_path++;
	}
	ret = (int)ceil((double)(graph->nb_ants - nb_path + total_path_dist)
	/ (double)nb_path);
	return (ret);
}

void		augment_flow(t_graph *graph)
{
	int		current;
	t_edge	*edge;
	t_edge	*reverse_edge;

	current = graph->end;
	while (current != graph->start)
	{
		edge = give_edge(graph, current, graph->tab[PARENT][current]);
		reverse_edge = give_edge(graph, graph->tab[PARENT][current], current);
		if (reverse_edge->is_full)
			reverse_edge->is_full = 0;
		else
			edge->is_full = 1;
		current = graph->tab[PARENT][current];
	}
}

void		reset_ways(t_graph *graph)
{
	t_node *node;
	t_edge *edge;

	node = graph->head;
	while (node)
	{
		edge = node->edges_l;
		while (edge)
		{
			edge->wrong_way = 0;
			edge = edge->next;
		}
		node = node->next;
	}
}
