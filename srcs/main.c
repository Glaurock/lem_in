/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:13:04 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/26 17:45:57 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ant		*create_ant(t_graph *graph, t_node *path, t_node **tmp)
{
	t_ant *ant;

	ant = (t_ant*)ft_memalloc(sizeof(t_ant));

	ant->path = path;
	ant->current = path->next;
	ant->next = graph->list_ants;
	graph->list_ants = ant;
	(*tmp)->is_free = 0;
	graph->nb_ants--;
}

void		mark_path(t_graph *graph, t_node *path)
{
	t_node *node;

	while (path)
	{
		if (path->number != graph->end && path->number != graph->start)
		{
			node = give_node(graph, path->number);
			node->is_a_path = 1;
		}
		path = path->next;
	}
}

void		recursive_loop(t_graph *graph, int previous_dist)
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
		ant = create_ant(graph, path, &tmp);
		//on marque le chemin A FAIRE
		mark_path(graph, path);
	}
	else
		size += graph->nb_ants;
	ft_dprintf(2, "size: %d\n", size);
	//recursive_loop(graph, size);
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
}

/*
** on s'arrete quand on a trouver tous les chemins possibles ou 
** quand la taille du chemin est superieur au chemin mini + nb_ants ( non implementer )
*/

void	find_all_path(t_graph *graph)
{
	t_node	*path;
	int		i;

	ft_bzero((void*)graph->tab_path, sizeof(graph->tab_path));
	while ((path = dijkstra_algo(graph, graph->start, graph->end)) != NULL)
	{
		graph->tab_path[graph->nb_path].head_path = path;
		mark_path(graph, path);
		graph->nb_path++;
		print_path(graph->tab_path[graph->nb_path - 1].head_path);
	}
}

/*
** a chaque tour, on remplit tous les chemins (pas bon ca???)
*/

void	game_loop(t_graph *graph)
{
	int		i;
	t_node	*path;
	t_node	*node;
	//fonction update game : pour chaque fourmi, la mettre a la position suivante
	//update_ants(graph);
	//recursive_loop(graph, 0);
	i = 0;
	while (graph->nb_ants && i < graph->nb_path)
	{
		path = graph->tab_path[i].head_path;
		node = give_node(graph, path->next->number);
		if (node->is_free)
			create_ant(graph, path, &node);
		i++;
	}
}


int		main(int argc, char **argv)
{
	t_graph		*graph;

	graph = (t_graph*)ft_memalloc(sizeof(t_graph));
	get_input(graph);
	ft_dprintf(2, "start : %d, end: %d\n", graph->start, graph->end);
	find_all_path(graph);
	game_loop(graph);
	print_graph(graph);
	del_graph(graph);
	return (0);
}
//ft_dprintf(2, "start: %d, end: %d, nb_ants:%d\n", graph->start, graph->end, graph->nb_ants);
