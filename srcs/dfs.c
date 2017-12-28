/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 09:22:28 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/28 09:30:38 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


void		depth_first_search(t_graph *graph, t_node *current, int **tab, int *path_index)
{
	t_edge	*edge;
	//int		*copy_tab;

	tab[SEEN][current->number] = true;
	tab[PATH][*path_index] = current->number;
	(*path_index)++;

	if (current->number == graph->start)
	{
		for (int i = 0; i < *path_index; i++)
			ft_dprintf(2, "%d | ", tab[PATH][i]);
		ft_dprintf(2, "\n");
		//mallcheck(copy_tab = (int*)ft_memalloc(sizeof(int) * graph->nb_sommets));
		//ft_memcpy(copy_tab, tab[PATH], sizeof(int) * graph->nb_sommets);
		ft_lstadd(&graph->list_tmp, ft_lstnew((void*)tab[PATH], sizeof(int) * graph->nb_sommets));
		reverse_tab((int*)(graph->list_tmp->content), *path_index);
	}
	else
	{
	//ft_dprintf(2, "current : (%d)\n", current->number);
		edge = current->edges_l;
		while (edge)
		{
			//if (tab[edge->links_to->number] == tab[current->number] - 1)
			//{
				//push_node_on_path(&path, edge->links_to);
			if (tab[WEIGHT][edge->links_to->number] == tab[WEIGHT][current->number] - 1)
				depth_first_search(graph, edge->links_to, tab, path_index);
			//}
			edge = edge->next;
		}
	}
	(*path_index)--;
	tab[SEEN][current->number] = false;
	//push_path_on_list_path(&graph->list_paths, path);
}

t_list	*select_best_path(t_graph *graph)
{
	

}

void	find_all_path(t_graph *graph)
{
	//t_node	*path;
	int		i;

	//ft_bzero((void*)graph->tab_path, sizeof(graph->tab_path));
	i = 0;
	give_weight(graph, graph->start, graph->end);
	select_best_path(graph);

	//while (i < 2 && dijkstra_algo(graph, graph->start, graph->end))
//	{
//		mark_path(graph);
//		i++;
//		graph->nb_path++;
//		if (!check_all_tag(graph))
//			break ;
		//print_path(graph->tab_path[graph->nb_path - 1].head_path);
//	}
}


