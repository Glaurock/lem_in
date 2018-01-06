/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 09:12:49 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 13:32:30 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	transform_list_in_tab(t_graph *graph)
{
	t_node	*current;
	int		i;

	if (!graph->head)
		return ;
	mallcheck(graph->tab_nodes = (t_node**)malloc(sizeof(t_node*)
	* graph->nb_sommets));
	current = graph->head;
	i = 0;
	while (current)
	{
		graph->tab_nodes[i] = current;
		current = current->next;
		i++;
	}
}
