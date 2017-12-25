/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 16:19:31 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/25 17:04:36 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_edge(t_graph *graph, char *line)
{
	char	*name1;
	char	*name2;
	t_node	*node1;
	t_node	*node2;
	int		i;

	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	line[i] = '\0';
	name1 = line;
	name2 = &line[i + 1];
	node1 = give_node_name(graph, name1);
	node2 = give_node_name(graph, name2);
	//ft_dprintf(2, "name1: %s, name2: %s\n", name1, name2);
	//ft_dprintf(2, "node1: %s, node2: %s\n", node1->name, node2->name);
	add_edge(give_node_name(graph, name1), give_node_name(graph, name2));
}

static void	read_edge(t_graph *graph, char *line)
{
	get_edge(graph, line);
	free(line);
	while (get_next_line(0, &line) > 0)
	{
		get_edge(graph, line);
		free(line);
	}
}

void	get_input(t_graph *graph)
{
	char	*line;
	int		i;

	get_next_line(0, &line);
	//ft_dprintf(2, "%s\n", line);
	if (!ft_isdigit(line[0]))
	{
		free(line);
		die("can't get ants number");
	}
	else
	{
		graph->nb_ants = ft_atoi(&line[0]);
		ft_dprintf(2, "nb ants : %d\n", graph->nb_ants);
		free(line);
	}
	while (get_next_line(0, &line) > 0)
	{
		//ft_dprintf(2, "line dans boucle: %s\n", line);
		if (ft_strchr(line, '-'))
			break ;
		if (ft_strcmp(line, "##start") == 0)
		{
			free(line);
			get_next_line(0, &line);
			graph->start = graph->nb_sommets;
		}
		if (ft_strcmp(line, "##end") == 0)
		{
			free(line);
			get_next_line(0, &line);
			graph->end = graph->nb_sommets;
		}
		i = 0;
		while (line[i] && line[i] != ' ')
			i++;
		line[i] = '\0';
		//ft_dprintf(2, "line cut: %s\n", line);
		push_end(graph, create_node(graph->nb_sommets, line));
		free(line);
		graph->nb_sommets++;
	}
	read_edge(graph, line);
}
