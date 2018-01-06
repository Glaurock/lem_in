/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:24:30 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 15:07:19 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	cancelling_negative_path(t_graph *graph)
{
	int path_index;
	t_list *list;

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

	//verif 
	list = graph->list_paths;
	while (list)
	{
		print_tab((int*)list->content, graph->nb_sommets, graph->end);
		list = list->next;
	}

	print_graph(graph);
}

void	find_path(t_graph *graph)
{
	int path_index;
	int test;
	int max_flow_is_best;

	mallcheck(graph->tab[SEEN] = (int*)ft_memalloc(sizeof(int) * graph->nb_sommets));
	mallcheck(graph->tab[PARENT] = (int*)ft_memalloc(sizeof(int) * graph->nb_sommets));
	mallcheck(graph->tab[PATH] = (int*)ft_memalloc(sizeof(int) * graph->nb_sommets));
	graph->best = INF;

	//print_graph(graph);
	while (bfs(graph))
	{
		augment_flow(graph);

		ft_bzero(graph->tab[SEEN], sizeof(int) * graph->nb_sommets);
		path_index = 0;
		dfs(graph, graph->tab_nodes[graph->start], &path_index);
		//ft_dprintf(2, "Nb tour: %d\n", calc_nb_lap(graph));
		test = calc_nb_lap(graph, 0);
		ft_dprintf(2, "test: %d\n", test);
		max_flow_is_best = 0;
		if (test < graph->best)
		{
			// save les meilleurs chemins
			save_best_paths(graph);
			graph->best = test;
			max_flow_is_best = 1;
		}
		ft_lstdel(&graph->list_tmp, &free_tab_in_list);
		// verif
		//for (int i = 0; i < graph->nb_sommets; i++)
		//	ft_dprintf(2, "tab[%d] : %d || ", i, graph->tab[PARENT][i]);
		//ft_dprintf(2, "\n");
	}


	//verif 
	t_list *list = graph->list_paths;
	while (list)
	{
		print_tab((int*)list->content, graph->nb_sommets, graph->end);
		list = list->next;
	}
	if (max_flow_is_best)
		cancelling_negative_path(graph);
	sort_by_size(graph);
}
