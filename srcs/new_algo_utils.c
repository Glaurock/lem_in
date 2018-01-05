/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_algo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:16:05 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/05 14:18:21 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_edge		*give_edge(t_graph *graph, int son, int parent)
{
	t_edge *edge;
	t_node *node;

	node = graph->tab_nodes[parent];
	edge = node->edges_l;
	while (edge)
	{
		if (edge->links_to->number == son)
			return (edge);
		edge = edge->next;
	}
	return (NULL);
}

int			calc_nb_lap(t_graph *graph)
{
	int ret;
	int total_path_dist;
	int nb_path;
	t_list *list;

	ret = 0;
	total_path_dist = 0;
	nb_path = 0;
	list = graph->list_tmp;
	while (list)
	{
		total_path_dist +=  count_path_size((int*)list->content, graph->nb_sommets, graph->end);
		list = list->next;
		nb_path++;
	}
	//ft_dprintf(2, "total path dist: %d\n", total_path_dist);
	ret = (int)ceil((double)(graph->nb_ants - nb_path + total_path_dist) / (double)nb_path);
	return (ret);
}

void		augment_flow(t_graph *graph)
{
	int		current;
	t_edge	*edge;
	t_edge	*reverse_edge;

	current = graph->end;
	while (current != graph->start)
	{
		edge = give_edge(graph, current, graph->tab[PARENT][current]);
		reverse_edge = give_edge(graph, graph->tab[PARENT][current], current);
		//ft_dprintf(2, "current edge: %d\n", edge->links_to->number);
		if (reverse_edge->is_full)
			reverse_edge->is_full = 0;
		else
			edge->is_full = 1;
		current = graph->tab[PARENT][current];
	}
}

static t_list	*pop(t_list **list)
{
	t_list *tmp;

	if (!list || !*list)
		return (NULL);
	tmp = *list;
	*list = (*list)->next;
	return (tmp);
}

int		bfs(t_graph *graph)
{
	t_list *stack;
	t_list *poped;
	t_edge *edge;

	stack = NULL;
	ft_bzero(graph->tab[PARENT], sizeof(int) * graph->nb_sommets);
	ft_bzero(graph->tab[SEEN], sizeof(int) * graph->nb_sommets);
	//if (graph->tab_nodes[1])
	//ft_dprintf(2, "tab: %d\n", graph->tab_nodes[1]->number);
	ft_lstadd(&stack, ft_lstnew(graph->tab_nodes[graph->start], sizeof(t_node)));
	//ft_dprintf(2, "\nstack: %d\n", ((t_node*)stack->content)->number);

	graph->tab[SEEN][graph->start] = true;
	graph->tab[PARENT][graph->start] = -1;

	while (stack)
	{
		poped = pop(&stack);
		edge = ((t_node*)poped->content)->edges_l;

		while (edge)
		{
			//ft_dprintf(2, "edge from: (%d) to (%d) is %s \n", ((t_node*)poped->content)->number, edge->links_to->number, edge->is_full ? "full" : "empty");
			if (graph->tab[SEEN][edge->links_to->number] == false && !edge->is_full)
			{
				ft_lstadd_end(&stack, ft_lstnew(graph->tab_nodes[edge->links_to->number], sizeof(t_node)));
				graph->tab[PARENT][edge->links_to->number] = ((t_node*)poped->content)->number;
				graph->tab[SEEN][edge->links_to->number] = true;
				//free(poped);
				if (edge->links_to->number == graph->end)
					return (true); // free la liste en mettant une condition pour sortir des deux whiles
			}
			edge = edge->next;
		}
	}
	return (false);
}
