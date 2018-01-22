/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:24:30 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/22 13:04:33 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		cancelling_negative_path(t_graph *graph)
{
	int		path_index;

	path_index = 0;
	ft_dprintf(2, "\n--------cancelling algo --------\n");
	construct_residual_graph(graph);
	while (find_negative_path(graph))
	{
		adjust_negative_cycle(graph);
		reset_ways(graph);
		construct_residual_graph(graph);
	}
	ft_lstdel(&graph->list_paths, &free_tab_in_list);
	ft_lstdel(&graph->list_tmp, &free_tab_in_list);
	path_index = 0;
	dfs(graph, give_node(graph, graph->start), &path_index);
	save_best_paths(graph);
}

static void	malloc_tabs(t_graph *graph)
{
	mallcheck(graph->tab[SEEN] = (int*)ft_memalloc(sizeof(int)
	* graph->nb_sommets));
	mallcheck(graph->tab[PARENT] = (int*)ft_memalloc(sizeof(int)
	* graph->nb_sommets));
	mallcheck(graph->tab[PATH] = (int*)ft_memalloc(sizeof(int)
	* graph->nb_sommets));
}

void		find_path(t_graph *graph)
{
	int path_index;
	int test;
	int max_flow_is_best;

	malloc_tabs(graph);
	graph->best = INF;
	while (bfs(graph))
	{
		augment_flow(graph);
		ft_bzero(graph->tab[SEEN], sizeof(int) * graph->nb_sommets);
		path_index = 0;
		dfs(graph, graph->tab_nodes[graph->start], &path_index);
		test = calc_nb_lap(graph, 0);
		max_flow_is_best = 0;
		if (test < graph->best)
		{
			save_best_paths(graph);
			graph->best = test;
			max_flow_is_best = 1;
		}
		ft_lstdel(&graph->list_tmp, &free_tab_in_list);
	}
	if (max_flow_is_best)
		cancelling_negative_path(graph);
	sort_by_size(graph);
}
