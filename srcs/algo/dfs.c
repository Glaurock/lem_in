/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 09:22:28 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 13:12:05 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		dfs(t_graph *graph, t_node *current, int *path_index)
{
	t_edge	*edge;

	graph->tab[PATH][*path_index] = current->number;
	(*path_index)++;
	if (current->number == graph->end)
		ft_lstadd(&graph->list_tmp, ft_lstnew((void*)graph->tab[PATH],
		sizeof(int) * graph->nb_sommets));
	else
	{
		edge = current->edges_l;
		while (edge)
		{
			if (edge->is_full)
				dfs(graph, edge->links_to, path_index);
			edge = edge->next;
		}
	}
	(*path_index)--;
}
