/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:13:04 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/29 18:29:09 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** on s'arrete quand on a trouver tous les chemins possibles ou 
** quand la taille du chemin est superieur au chemin mini + nb_ants ( non implementer )
*/

void	game_loop(t_graph *graph)
{
	int		i;
	//t_node	*path;
	int		*map;
	t_list	*list;
	t_node	*node;
	int		last_dist;

	graph->space = 0;
	ft_dprintf(2, "------Start game loop-----\n\n");
	//fonction update game : pour chaque fourmi, la mettre a la position suivante
	update_ants(graph);
	//ft_dprintf(2, "nb active ants: %d\n", size_ants(graph->list_ants));
	i = 0;
	last_dist = 0;
	list = graph->list_paths;
	while (graph->nb_ants && list)
	{
		map = (int*)(list->content);
		node = give_node(graph, map[1]);
		//ft_dprintf(2, "test boucle");
		if (!i)
			create_ant(graph, map, &node);
		else if (node->is_free && last_dist + graph->nb_ants > count_path_size(map, graph->nb_sommets, graph->end) - 1)
				create_ant(graph, map, &node);
		list = list->next;
		i++;
		last_dist = count_path_size(map, graph->nb_sommets, graph->end) - 1;
	}
	//print_graph(graph);
	//ft_dprintf(2, "nb_ants : %d, arrived : %d\n", graph->nb_ants, graph->arrived);
	ft_printf("\n");
}

int		main(int argc, char **argv)
{
	t_graph		*graph;
	int			nb_start;
	int			i;

	mallcheck(graph = (t_graph*)ft_memalloc(sizeof(t_graph)));
	get_input(graph);
	ft_dprintf(2, "start : %d, end: %d\n", graph->start, graph->end);
	find_all_path(graph);
	if (!graph->list_paths)
		free_all(graph, "No path found");
	mallcheck(graph->tab_ants = (t_ant**)ft_memalloc(sizeof(t_ant*) * (graph->nb_ants + 1)));
	nb_start = graph->nb_ants;
	//while (graph->arrived != nb_start)
	//	game_loop(graph);
	//print_graph(graph);
	free_all(graph, 0);
	return (0);
}
