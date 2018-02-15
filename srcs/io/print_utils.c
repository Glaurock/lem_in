/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fauconfan <fauconfan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 18:06:47 by fauconfan         #+#    #+#             */
/*   Updated: 2018/02/15 18:07:06 by fauconfan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_list_tmp(t_list *current, int size, int end)
{
	ft_dprintf(2, "print_list_tmp: \n");
	while (current)
	{
		print_tab((int*)current->content, size, end);
		current = current->next;
	}
}

void		print_weight(int **tab, int size)
{
	int i;

	ft_dprintf(2, "\nprint_tab :\n");
	i = -1;
	while (++i < size)
		ft_dprintf(2, "weight[%d]: %-3d || path: %d\n", i,
		tab[WEIGHT][i], tab[PATH][i]);
}

void		print_tab(int *tab, int size, int end)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		ft_dprintf(2, "(%d) || ", tab[i]);
		if (tab[i] == end)
		{
			ft_dprintf(2, "\n");
			return ;
		}
	}
	ft_dprintf(2, "\n");
}

void		print_graph(t_graph *graph)
{
	t_node	*node;
	t_edge	*edge;

	if (!graph)
		return ;
	node = graph->head;
	if (!node)
	{
		ft_dprintf(2, "Pas de premier sommet dans le graphe\n");
		return ;
	}
	while (node)
	{
		ft_dprintf(2, "Number : (%d), name : (%s) ", node->number, node->name);
		edge = node->edges_l;
		while (edge)
		{
			ft_dprintf(2, "LINKS TO (%s) , %s , %d, %s	",
			edge->links_to->name, edge->is_full ? "full" : "empty",
			edge->w, edge->wrong_way ? "wrong_way" : "OK");
			edge = edge->next;
		}
		node = node->next;
		ft_dprintf(2, "\n");
	}
}
