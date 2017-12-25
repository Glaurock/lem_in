/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 16:22:01 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/25 18:06:31 by gmonnier         ###   ########.fr       */
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

void		print_weight(int **tab, int size)
{
	int i;

	ft_dprintf(2, "\nprint_tab :\n");
	i = -1;
	while (++i < size)
	{
		ft_dprintf(2, "weight[%d]: %-3d || %s\n", i, tab[WEIGHT][i], tab[SEEN][i] == true ? "true" : "false" );
	}
}

void		print_path(t_node **tab_previous, int start, int end)
{
	int		i;
	t_node	*current;

	current = tab_previous[end];
	ft_dprintf(2, "%d --> ", end);
	while (current->number != start)
	{
		if (current)
			ft_dprintf(2, "%d --> ", current->number);
		current = tab_previous[current->number];
	}
	ft_dprintf(2, "%d\n", start);
}

t_node		**dijkstra_algo(t_graph *graph, int start, int end)
{
	t_edge	*path;
	int		*tab[2];
	t_node	**tab_previous;
	int		i;
	t_node	*current;
	t_edge	*edge;
	int		i_son;
	int		i_father;

	ft_dprintf(2, "--------Start aglo--------\n\n");
	path = NULL;
	tab[SEEN] = (int*)malloc(sizeof(int) * graph->nb_sommets);
	tab[WEIGHT] = (int*)malloc(sizeof(int) * graph->nb_sommets);
	tab_previous = (t_node**)malloc(sizeof(t_node*) * graph->nb_sommets);

	i = -1;
	while (++i < graph->nb_sommets)
	{
		tab[WEIGHT][i] = -1;
		tab[SEEN][i] = false;
		tab_previous[i] = NULL;
	}
	tab[WEIGHT][start] = 0;

	/* debut algo */
	/* tant que le noeud ayant le poids le plus faible n'est pas end */

	i_father = get_index_min_weight(tab, graph->nb_sommets);
	i = 0;
	while (i_father != end)
	{
		i_father = get_index_min_weight(tab, graph->nb_sommets);
		//ft_dprintf(2, "i_father : %d\n", i_father);
		tab[SEEN][i_father] = true;

		/* on parcours les fils du noeud */

		current = give_node(graph, i_father);
		edge = current->edges_l;
		while (edge)
		{
			i_son = edge->links_to->number;
			/* si le noeud n'a pas encore ete parcouru */
			if (tab[SEEN][i_son] == false)
			{
				if (tab[WEIGHT][i_son] == -1 ||
				(tab[WEIGHT][i_father] + 1 < tab[WEIGHT][i_son]))
				{
					tab[WEIGHT][i_son] = tab[WEIGHT][i_father] + 1;
					tab_previous[i_son] = current;
				}
			}
			edge = edge->next;
		}
		print_weight(tab, graph->nb_sommets);
	}
	/* on retrouve le chemin a emprunter */
	print_path(tab_previous, start, end);
	free(tab[WEIGHT]);
	free(tab[SEEN]);
	return (tab_previous); // to free
}
