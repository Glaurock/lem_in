/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:13:04 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/22 12:58:15 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	game_loop(t_graph *graph)
{
	int		i;
	int		*map;
	t_list	*list;
	t_node	*node;

	graph->space = 0;
	ft_dprintf(2, "------Start game loop-----\n\n");
	update_ants(graph);
	i = 0;
	list = graph->list_paths;
	while (graph->nb_ants && list)
	{
		map = (int*)(list->content);
		node = give_node(graph, map[1]);
		if (!i)
			create_ant(graph, map, &node);
		else if (node->is_free && calc_nb_lap(graph, 1) >=
		count_path_size(map, graph->nb_sommets, graph->end))
			create_ant(graph, map, &node);
		list = list->next;
		i++;
	}
	ft_printf("\n");
}

int		main(void)
{
	t_graph		*graph;
	int			nb_start;

	mallcheck(graph = (t_graph*)ft_memalloc(sizeof(t_graph)));
	get_input(graph);
	ft_dprintf(2, "start : %d, end: %d\n", graph->start, graph->end);
	transform_list_in_tab(graph);
	find_path(graph);
	if (!graph->list_paths)
		free_all(graph, "No path found");
	mallcheck(graph->tab_ants = (t_ant**)ft_memalloc(sizeof(t_ant*)
	* (graph->nb_ants + 1)));
	nb_start = graph->nb_ants;
	while (graph->arrived != nb_start)
		game_loop(graph);
	free_all(graph, 0);
	return (0);
}
