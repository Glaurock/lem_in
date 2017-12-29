/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:27:50 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/29 15:34:39 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


/*
** on cree une fourmi, on la push a la fin de la liste, 
** on met la position a not_free
*/

void		create_ant(t_graph *graph, int *map, t_node **tmp)
{
	t_ant *ant;

	mallcheck(ant = (t_ant*)ft_memalloc(sizeof(t_ant)));
	//check malloc

	graph->tab_ants[graph->index] = ant;
	ant->map = map;
	ant->index = 1;
	(*tmp)->is_free = 0;
	graph->nb_ants--;
	graph->index++;
	if (graph->space)
		ft_printf(" ");
	ft_printf("L%d-%d", graph->index, (*tmp)->number);
	graph->space = 1;
}

int		check_arrived(t_graph *graph, t_ant **ant)
{
	if (*ant && (*ant)->map[(*ant)->index] == graph->end)
	{
		ft_dprintf(2, "Arrived!!!\n");
		ft_memdel((void**)ant);
		graph->arrived++;
		return (1);
	}
	return (0);
}

void	update_ants(t_graph *graph)
{
	t_node	*tmp;
	int		i;
	t_ant	*ant;

	i = -1;
	while (++i < graph->index)
	{
		//print_path(ant->path);
		ant = graph->tab_ants[i];
		check_arrived(graph, &ant);
		if (!ant)
			continue ;
		tmp = give_node(graph, ant->map[ant->index]);
		//ft_dprintf(2, "tmp :%d\n", tmp->number);
		tmp->is_free = 1;
		ant->index++;
		if (graph->space)
			ft_printf(" ");
		ft_printf("L%d-%d", i + 1, ant->map[ant->index]);
		graph->space = 1;
		if (!check_arrived(graph, &ant))
		{
			tmp = give_node(graph, ant->map[ant->index]);
			tmp->is_free = 0;
		}
	}
}
