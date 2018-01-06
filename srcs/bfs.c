/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 11:39:31 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 15:14:47 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	edge_loop(t_graph *graph, t_list *poped, int *check, t_list **stack)
{
	t_edge *edge;

	edge = ((t_node*)poped->content)->edges_l;
	while (edge && check)
	{
		if (graph->tab[SEEN][edge->links_to->number] == FALSE && !edge->is_full)
		{
			ft_lstadd_end(stack,
			ft_lstnew(graph->tab_nodes[edge->links_to->number],
			sizeof(t_node)));
			graph->tab[PARENT][edge->links_to->number] =
			((t_node*)poped->content)->number;
			graph->tab[SEEN][edge->links_to->number] = TRUE;
			if (edge->links_to->number == graph->end)
				*check = 0;
		}
		edge = edge->next;
	}
}

int			bfs(t_graph *graph)
{
	t_list	*stack;
	t_list	*poped;
	int		check;

	stack = NULL;
	ft_bzero(graph->tab[PARENT], sizeof(int) * graph->nb_sommets);
	ft_bzero(graph->tab[SEEN], sizeof(int) * graph->nb_sommets);
	ft_lstadd(&stack, ft_lstnew(graph->tab_nodes[graph->start],
	sizeof(t_node)));
	graph->tab[SEEN][graph->start] = TRUE;
	graph->tab[PARENT][graph->start] = -1;
	check = 1;
	while (stack && check)
	{
		poped = ft_lst_pop(&stack);
		edge_loop(graph, poped, &check, &stack);
		free(poped->content);
		free(poped);
	}
	ft_lstdel(&stack, &free_tab_in_list);
	return (check == 1 ? FALSE : TRUE);
}
