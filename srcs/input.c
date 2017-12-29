/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 16:19:31 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/29 18:22:20 by gmonnier         ###   ########.fr       */
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
	if (!node1 || !node2)
		free_all(graph, "Can't add edge and/or unknow node");
	add_edge(node1, node2);
}

static void	read_edge(t_graph *graph, char *line)
{
	if (ft_strchr(line, '-') == 0)
		free_all(graph, "Error to read edges");
	if (line[0] != '#')
		get_edge(graph, line);
	ft_memdel((void**)&line);
	while (get_next_line(0, &line) > 0)
	{
		if (line[0] != '#')
		{
			get_edge(graph, line);
			ft_memdel((void**)&line);
		}
	}
}

void	special_char(t_graph *graph, char **line, int *check)
{
	int a;

	a= 0;
	if (ft_strcmp(*line, "##start") == 0)
		a = 1;
	else if (ft_strcmp(*line, "##end") == 0)
		a = 2;
	free(*line);
	if (a)
	{
		get_next_line(0, line);
		a == 1 ? graph->start = graph->nb_sommets : 0;
		a == 2 ? graph->end = graph->nb_sommets : 0;
		(*check)++;
	}
}

void	get_input(t_graph *graph)
{
	char	*line;
	int		i;
	int		check;

	check = 0;
	if (get_next_line(0, &line) <= 0)
		free_all(graph, "Can't read input and/or empty input");
	if (!ft_isdigit(line[0]))
	{
		free(line);
		free_all(graph, "Can't get ants number");
	}
	else
	{
		graph->nb_ants = ft_atoi(&line[0]);
		ft_dprintf(2, "nb ants : %d\n", graph->nb_ants);
		free(line);
	}
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strchr(line, '-'))
			break ;
		if (line[0] == '#')
			special_char(graph, &line, &check);
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
	if (graph->start == graph->end || check != 2)
		free_all(graph, "Error input start and/or end");
}
