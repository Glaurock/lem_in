/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:27:50 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 14:32:37 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_arrived(t_graph *graph, int i)
{
	t_ant *ant;

	ant = graph->tab_ants[i];
	if (ant && ant->map[ant->index] == graph->end)
	{
		ft_dprintf(2, "Arrived!!!\n");
		ft_memdel((void**)&graph->tab_ants[i]);
		graph->arrived++;
		return (1);
	}
	return (0);
}

void		create_ant(t_graph *graph, int *map, t_node **tmp)
{
	t_ant *ant;

	mallcheck(ant = (t_ant*)ft_memalloc(sizeof(t_ant)));
	ft_dprintf(2, "\nCreate ant\n");
	graph->tab_ants[graph->index] = ant;
	ant->map = map;
	ant->index = 1;
	(*tmp)->is_free = 0;
	graph->nb_ants--;
	graph->index++;
	if (graph->space)
		ft_printf(" ");
	ft_printf("L%d-%s", graph->index, (*tmp)->name);
	check_arrived(graph, graph->index - 1);
	graph->space = 1;
}

void	update_ants(t_graph *graph)
{
	t_node	*tmp;
	int		i;
	t_ant	*ant;
	t_node	*node_name;

	i = -1;
	while (++i < graph->index)
	{
		ant = graph->tab_ants[i];
		if (!ant)
			continue ;
		tmp = give_node(graph, ant->map[ant->index]);
		//ft_dprintf(2, "tmp :%d\n", tmp->number);
		tmp->is_free = 1;
		ant->index++;
		if (graph->space)
			ft_printf(" ");
		node_name = give_node(graph, ant->map[ant->index]);
		ft_printf("L%d-%s", i + 1, node_name->name);
		graph->space = 1;
		if (!check_arrived(graph, i))
		{
			tmp = give_node(graph, ant->map[ant->index]);
			tmp->is_free = 0;
		}
	}
}
