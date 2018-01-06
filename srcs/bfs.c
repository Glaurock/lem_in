/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 11:39:31 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 11:52:56 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		bfs(t_graph *graph)
{
	t_list *stack;
	t_list *poped;
	t_edge *edge;
	int	check;

	stack = NULL;
	ft_bzero(graph->tab[PARENT], sizeof(int) * graph->nb_sommets);
	ft_bzero(graph->tab[SEEN], sizeof(int) * graph->nb_sommets);
	//if (graph->tab_nodes[1])
	//ft_dprintf(2, "tab: %d\n", graph->tab_nodes[1]->number);
	ft_lstadd(&stack, ft_lstnew(graph->tab_nodes[graph->start], sizeof(t_node)));
	//ft_dprintf(2, "\nstack: %d\n", ((t_node*)stack->content)->number);

	graph->tab[SEEN][graph->start] = true;
	graph->tab[PARENT][graph->start] = -1;
	check = 1;
	while (stack && check)
	{
		poped = ft_lst_pop(&stack);
		edge = ((t_node*)poped->content)->edges_l;

		while (edge && check)
		{
			//ft_dprintf(2, "edge from: (%d) to (%d) is %s \n", ((t_node*)poped->content)->number, edge->links_to->number, edge->is_full ? "full" : "empty");
			if (graph->tab[SEEN][edge->links_to->number] == false && !edge->is_full)
			{
				ft_lstadd_end(&stack, ft_lstnew(graph->tab_nodes[edge->links_to->number], sizeof(t_node)));
				graph->tab[PARENT][edge->links_to->number] = ((t_node*)poped->content)->number;
				graph->tab[SEEN][edge->links_to->number] = true;
				//free(poped);
				if (edge->links_to->number == graph->end)
					check = 0;
			}
			edge = edge->next;
		}
		free(poped->content);
		free(poped);
	}
	ft_lstdel(&stack, &free_tab_in_list);
	return (check == 1 ? false : true);
}
