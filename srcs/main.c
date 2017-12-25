/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:13:04 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/25 18:04:46 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int argc, char **argv)
{
	t_graph		*graph;

	graph = (t_graph*)ft_memalloc(sizeof(t_graph));
	get_input(graph);
	dijkstra_algo(graph, 2, 4);
	print_graph(graph);
	del_graph(graph);
	return (0);
}
//ft_dprintf(2, "start: %d, end: %d, nb_ants:%d\n", graph->start, graph->end, graph->nb_ants);
