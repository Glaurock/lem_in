/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:13:04 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/25 23:05:21 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ant		*create_ant(t_node *path)
{
	t_ant *ant;

	ant = (t_ant*)ft_memalloc(sizeof(t_ant));

	ant->next = NULL;
	ant->path = path;
	ant->current = path;
}

void	recursive_loop(t_graph *graph, int previous_dist)
{
	t_node	*path;
	int		size;
	t_node	*tmp;
	t_ant	*ant;

	path = dijkstra_algo(graph, graph->start, graph->end); // to free

	size = ft_path_size(path) - 1;
	if (size < previous_dist || !graph->nb_ants || !path)
	{
		ft_dprintf(2, "out of recursive_loop\n");
		return ;
	}
	tmp = give_node(graph, path->next->number);
	//ft_dprintf(2, "tmp node: %d\n", tmp->number);
	
	// pas fourmi devant
	if (tmp->is_free)
	{
		//on cree une fourmi avec son path
		ant = create_ant(path);
		ant->next = graph->list_ants;
		graph->list_ants = ant;
		
		//on fait avancer la fourmi
		ant->current = ant->current->next;
		tmp->is_free = 0;
		//on marque le chemin A FAIRE
	}
	else
	{
		size += graph->nb_ants;
		// condition pour savoir si on cree une fourmi
	}
	ft_dprintf(2, "size: %d\n", size);
	
	//appeler la recursive ici avec la nouvelle size (dist)
}

void	update_ants(t_graph *graph)
{
	t_ant	*ants;
	t_node	*tmp;

	ants = graph->list_ants;
	while (ants)
	{
		// move ants here
		ants = ants->next;
	}
	//tmp = give_node(graph, 1);
	//tmp->is_free = 0;
}

void	game_loop(t_graph *graph)
{
	//fonction update game : pour chaque fourmi, la mettre a la position suivante
	update_ants(graph);
	recursive_loop(graph, 0);
}


int		main(int argc, char **argv)
{
	t_graph		*graph;

	graph = (t_graph*)ft_memalloc(sizeof(t_graph));
	get_input(graph);
	ft_dprintf(2, "start : %d, end: %d\n", graph->start, graph->end);
	game_loop(graph);
	print_graph(graph);
	del_graph(graph);
	return (0);
}
//ft_dprintf(2, "start: %d, end: %d, nb_ants:%d\n", graph->start, graph->end, graph->nb_ants);
