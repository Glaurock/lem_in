/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 16:22:01 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/25 22:14:01 by gmonnier         ###   ########.fr       */
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

/*
** attention, le path contiendra uniquement les numeros des sommets, et non leur nom
*/

t_node		*get_path(t_node **tab_previous, int start, int end)
{
	t_node	*path;
	t_node	*current;

	path = create_node(end, 0);
	current = path;
	while (current->number != start)
	{
		current->next = create_node(tab_previous[current->number]->number, 0);
		current = current->next;
	}
	free(tab_previous);
	ft_reverse_path(&path);
	return (path);
}

int			unreacheable_check(int **tab, int size)
{
	int i;
	int check;

	i = -1;
	check = 0;
	while (++i < size)
	{
		if (tab[SEEN][i] == false && tab[WEIGHT][i] != -1)
			check = 1;
	}
	return (check);
}

t_node		*dijkstra_algo(t_graph *graph, int start, int end)
{
	int		*tab[2];
	t_node	**tab_previous;
	int		i;
	t_node	*current;
	t_edge	*edge;
	int		i_son;
	int		i_father;
	t_node	*path;

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
		//ft_dprintf(2, "i_father : %d\n", i_father);
		tab[SEEN][i_father] = true;

		// on parcours les fils du noeud

		current = give_node(graph, i_father);
		//ft_dprintf(2, "current: %d\n", current->number);
		edge = current->edges_l;
		//ft_dprintf(2, "edges: %d\n", current->edges_l->links_to->number);
		while (edge)
		{
			i_son = edge->links_to->number;
			// si le noeud n'a pas encore ete parcouru 
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
		//print_weight(tab, graph->nb_sommets);
		// check for unreacheable nodes
		i_father = get_index_min_weight(tab, graph->nb_sommets);
		if (!unreacheable_check(tab, graph->nb_sommets))
			return (NULL);
	}
	/* on retrouve le chemin a emprunter */

	/* traite tab_previous pour obtenir le chemin */
	path = get_path(tab_previous, start, end);

	print_path(path);
	free(tab[WEIGHT]);
	free(tab[SEEN]);
	return (path); // to free
}
