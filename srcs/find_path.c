/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:24:30 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 10:53:55 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	save_best_paths(t_graph *graph)
{
	t_list *list;

	ft_lstdel(&graph->list_paths, &free_tab_in_list);
	list = graph->list_tmp;
	while (list)
	{
		ft_lstadd_end(&graph->list_paths, ft_lstnew(list->content, list->content_size));
		list = list->next;
	}
}

static void sort_by_size(t_graph *graph)
{
	t_list *list;
	int i;
	int size;
	int size1;
	int size2;

	i = 0;
	size = ft_lst_size(graph->list_paths);
	list = graph->list_paths;
	while (i < size)
	{
		list = graph->list_paths;
		while (list->next)
		{
			size1 = count_path_size((int*)list->content, graph->nb_sommets, graph->end);
			size2 = count_path_size((int*)list->next->content, graph->nb_sommets, graph->end);
			if (size1 > size2)
				ft_swap_ptr(&(list->content), &(list->next->content));
			list = list->next;
		}
		i++;
	}
}

void	find_path(t_graph *graph)
{
	int path_index;
	int test;

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
		test = calc_nb_lap(graph);
		ft_dprintf(2, "test: %d\n", test);
		if (test < graph->best)
		{
			// save les meilleurs chemins
			save_best_paths(graph);
			graph->best = test;
		}
		ft_lstdel(&graph->list_tmp, &free_tab_in_list);
		// verif
		//for (int i = 0; i < graph->nb_sommets; i++)
		//	ft_dprintf(2, "tab[%d] : %d || ", i, graph->tab[PARENT][i]);
		//ft_dprintf(2, "\n");
	}

	sort_by_size(graph);

	//verif 
	t_list *list = graph->list_paths;
	while (list)
	{
		print_tab((int*)list->content, graph->nb_sommets, graph->end);
		list = list->next;
	}

	//give_weight_to_edges(graph);
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
