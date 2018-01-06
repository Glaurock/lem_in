/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 09:37:47 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 11:32:55 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	find_nb_path(t_graph *graph)
{
	int		nb;
	int		nb2;
	t_node	*current;
	t_edge	*edge;

	nb = 0;
	current = give_node(graph, graph->start);
	edge = current->edges_l;
	while (edge)
	{
		nb++;
		edge = edge->next;
	}
	nb2 = 0;
	current = give_node(graph, graph->end);
	edge = current->edges_l;
	while (edge)
	{
		nb2++;
		edge = edge->next;
	}
	ft_dprintf(2, "nb1: %d, nb2: %d\n", nb, nb2);
	graph->nb_path = nb > nb2 ? nb2 : nb;
}

void		mark_path(t_graph *graph, int *tab)
{
	int		i;
	t_node	*node;

	i = -1;
	while (++i < graph->nb_sommets)
	{
		if (tab[i] == graph->end)
			return ;
		if (tab[i] != graph->start)
		{
			node = give_node(graph, tab[i]);
			node->is_a_path = 1;
			//graph->tab[WEIGHT][tab[i]] += TAG;
		}
	}
}

void		unmark_path(t_graph *graph, int *tab)
{
	int		i;
	t_node	*node;

	i = -1;
	while (++i < graph->nb_sommets)
	{
		if (tab[i] == graph->end)
			return ;
		if (tab[i] != graph->start)
		{
			node = give_node(graph, tab[i]);
			node->is_a_path = 0;
		}
	}
}

void		print_list_tmp(t_list *current, int size, int end)
{

	ft_dprintf(2, "print_list_tmp: \n");
	while (current)
	{
		print_tab((int*)current->content, size, end);
		current = current->next;
	}
}

int			count_path_size(int *tab, int size, int end)
{
	int i;

	i = -1;
	while (++i < size)
	{
		if (tab[i] == end)
			return (i);
	}
	return (i);
}
