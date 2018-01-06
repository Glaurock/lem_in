/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 15:33:02 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 15:43:16 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		already_an_edge(t_node *node1, t_node *node2)
{
	t_edge *edge;

	edge = node1->edges_l;
	while (edge)
	{
		if (edge->links_to == node2)
			return (1);
		edge = edge->next;
	}
	return (0);
}

int		get_edge(t_graph *graph, char *line)
{
	t_node	*node1;
	t_node	*node2;
	int		i;
	char	**splitted;

	if (!*line)
		return (-1);
	splitted = ft_strsplit(line, '-');
	node1 = give_node_name(graph, splitted[0]);
	node2 = give_node_name(graph, splitted[1]);
	i = -1;
	while (splitted[++i])
		free(splitted[i]);
	free(splitted);
	if (!node1 || !node2)
		return (-1);
	if (!already_an_edge(node1, node2))
		add_edge(node1, node2);
	return (1);
}

void	read_edge(t_graph *graph, char *line)
{
	if (ft_strchr(line, '-') == 0)
		return ;
	if (line[0] != '#' && get_edge(graph, line) == -1)
		return ;
	ft_memdel((void**)&line);
	while (get_next_line(0, &line) > 0)
	{
		if (line[0] != '#')
		{
			if (get_edge(graph, line) == -1)
			{
				ft_memdel((void**)&line);
				return ;
			}
			ft_printf("%s\n", line);
		}
		ft_memdel((void**)&line);
	}
}
