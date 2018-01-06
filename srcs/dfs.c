/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 09:22:28 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 11:44:08 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		dfs(t_graph *graph, t_node *current, int *path_index)
{
	t_edge	*edge;

	//graph->tab[SEEN][current->number] = true;
	graph->tab[PATH][*path_index] = current->number;
	(*path_index)++;
	if (current->number == graph->end)
	{
		//ft_dprintf(2, "Shortest path find: ");
		//for (int i = 0; i < *path_index; i++)
		//	ft_dprintf(2, "%d | ", tab[PATH][i]);
		//ft_dprintf(2, "\n");
		ft_lstadd(&graph->list_tmp, ft_lstnew((void*)graph->tab[PATH], sizeof(int) * graph->nb_sommets));
		//reverse_tab((int*)(graph->list_tmp->content), *path_index);
	}
	else
	{
		//ft_dprintf(2, "current : (%d)\n", current->number);
		edge = current->edges_l;
		//min_weight = give_min_weight(tab, edge);
		//ft_dprintf(2, "Min_weight: %d\n", min_weight);
		while (edge)
		{
			//if (min_weight >= TAG)
			//	break ;
			//if (tab[WEIGHT][edge->links_to->number] == tab[WEIGHT][current->number] + 1 && tab[SEEN][edge->links_to->number] == false && tab[WEIGHT][edge->links_to->number] < TAG)
			//if (tab[WEIGHT][edge->links_to->number] == min_weight && tab[SEEN][edge->links_to->number] == false)
			if (edge->is_full)
				dfs(graph, edge->links_to, path_index);
			edge = edge->next;
		}
	}
	(*path_index)--;
	//graph->tab[SEEN][current->number] = false;
	//push_path_on_list_path(&graph->list_paths, path);
	//print_weight(tab, graph->nb_sommets);
	//if (check_true(tab[SEEN], graph->nb_sommets))
//	{
//		ft_dprintf(2, "finish\n");
//	}
}
