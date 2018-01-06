/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   residual_graph.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 11:40:36 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 11:53:49 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	construct_residual_graph(t_graph *graph)
{
	t_list *stack;
	t_list *poped;
	t_edge *edge;
	t_edge *reverse_edge;

	stack = NULL;
	//ft_lstdel(&graph->list_tmp, &free_tab_in_list);
	ft_lstadd(&stack, ft_lstnew(graph->tab_nodes[graph->start], sizeof(t_node)));

	ft_bzero(graph->tab[SEEN], sizeof(int) * graph->nb_sommets);
	graph->tab[SEEN][graph->start] = true;
	
	while (stack)
	{
		poped = ft_lst_pop(&stack);
		edge = ((t_node*)poped->content)->edges_l;
		//ft_lstadd_end(&graph->list_tmp, ft_lstnew(poped->content, poped->content_size));
		while (edge)
		{
			//ft_dprintf(2, "edge from: (%d) to (%d) is %s \n", ((t_node*)poped->content)->number, edge->links_to->number, edge->is_full ? "full" : "empty");
			reverse_edge = give_edge(graph, ((t_node*)poped->content)->number, edge->links_to->number);
			if (graph->tab[SEEN][edge->links_to->number] == false && edge->links_to->number != graph->end)
			{
				ft_lstadd_end(&stack, ft_lstnew(graph->tab_nodes[edge->links_to->number], sizeof(t_node)));
				graph->tab[SEEN][edge->links_to->number] = true;
			}
			// donner un poids a l'edge, puis marquer l'edge inverse comme wrong way
			if (!edge->wrong_way && !reverse_edge->wrong_way) // une seule fois par coter normanelement
			{
				if (edge->is_full)
				{
					edge->wrong_way = 1;
					reverse_edge->w = -1;
				}
				else
				{
					edge->w = 1;
					reverse_edge = give_edge(graph, ((t_node*)poped->content)->number, edge->links_to->number);
					reverse_edge->wrong_way = 1;
				}
			}
			edge = edge->next;
		}
		free(poped->content);
		free(poped);
	}
}
