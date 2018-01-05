/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 09:12:49 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/05 09:18:44 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	aff_graph(t_graph *graph)
{
	int i;

	i = -1;
	while (++i < graph->nb_sommets)
	{
		ft_dprintf(2, "(%d) ", graph->tab_nodes[i]->number);
	}
}

void	transform_list_in_tab(t_graph *graph)
{
	t_node	*current;
	int		i;

	if (!graph->head)
		return ;
	mallcheck(graph->tab_nodes = (t_node**)malloc(sizeof(t_node*) * graph->nb_sommets));
	current = graph->head;
	i = 0;
	while (current)
	{
		graph->tab_nodes[i] = current;
		current = current->next;
		i++;
	}
}
