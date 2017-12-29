/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 16:22:01 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/29 18:15:22 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		get_index_min_weight(int **tab, int size)
{
	int i;
	int min;
	int ret;
	int first;

	i = -1;
	ret = 0;
	first = 1;
	while (++i < size)
	{
		if (first && tab[SEEN][i] == false && tab[WEIGHT][i] >= 0)
		{
			min = tab[WEIGHT][i];
			first = 0;
		}
		if (!first && tab[WEIGHT][i] <= min && tab[WEIGHT][i] >= 0 && tab[SEEN][i] == false)
		{
			ret = i;
			min = tab[WEIGHT][i];
		}
	}
	return (ret);
}

void		print_all_paths(t_graph *graph)
{
	t_list	*list;
	int		i;

	list = graph->list_paths;
	while (list)
	{
		i = -1;
		while (++i < graph->nb_sommets)
		{
			ft_dprintf(2, "%d --> ", ((int*)(list->content))[i]);
		}
		ft_dprintf(2, "\n");
		list = list->next;
	}
}

void			give_weight(t_graph *graph, int start, int end)
{
	int		i;
	t_node	*current;
	t_edge	*edge;
	int		i_son;
	int		i_father;
	t_node	*tmp_check;

	ft_dprintf(2, "--------Start weight--------\n\n");

	mallcheck(graph->tab[SEEN] = (int*)malloc(sizeof(int) * graph->nb_sommets));
	mallcheck(graph->tab[WEIGHT] = (int*)malloc(sizeof(int) * graph->nb_sommets));

	i = -1;
	while (++i < graph->nb_sommets)
	{
		graph->tab[WEIGHT][i] = -1;
		graph->tab[SEEN][i] = false;
	}
	graph->tab[WEIGHT][start] = 0;


	// tant qu on a pas parcouru tous les noeuds

	i_father = get_index_min_weight(graph->tab, graph->nb_sommets);
	i = 0;
	while (check_false(graph->tab[SEEN], graph->nb_sommets))
	{
		//print_weight(graph->tab, graph->nb_sommets);
		//ft_dprintf(2, "i_father : %d\n", i_father);
		graph->tab[SEEN][i_father] = true;

		// on parcours les fils du noeud

		current = give_node(graph, i_father);

		/* poids plus fort pour les nodes de path */
		if (current->is_a_path)
			graph->tab[WEIGHT][current->number] += TAG;

		//ft_dprintf(2, "current: %d\n", current->number);
		edge = current->edges_l;
		//ft_dprintf(2, "edges: %d\n", current->edges_l->links_to->number);
		while (edge)
		{
			i_son = edge->links_to->number;
			//ft_dprintf(2, "i_son : %d\n", i_son);
			// si le noeud n'a pas encore ete parcouru 
			//{
				if (graph->tab[WEIGHT][i_son] == -1 ||
				(graph->tab[WEIGHT][i_father] + 1 <= graph->tab[WEIGHT][i_son]))
				{
					if (graph->tab[SEEN][i_son] == false)
						graph->tab[WEIGHT][i_son] = graph->tab[WEIGHT][i_father] + 1;
				}
			//}
			edge = edge->next;
		}
		// check for unreacheable nodes
		i_father = get_index_min_weight(graph->tab, graph->nb_sommets);
		if (!unreacheable_check(graph->tab, graph->nb_sommets))
			return ; // probleme ici 
	}
}
