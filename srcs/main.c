/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:13:04 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/24 23:14:55 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int argc, char **argv)
{
	t_graph *graph;

	graph = new_graph(5);
	add_edge(graph, add_node(1, "un"), add_node(2, "deux"));
	add_edge(graph, add_node(3, "trois"), add_node(4, "quatre"));
	add_edge(graph, add_node(1, "un"), add_node(3, "trois"));
	//add_edge(graph, 1, 3);
	//add_edge(graph, 1, 4);
	print_graph(graph);
	del_graph(graph);
	return (0);
}
