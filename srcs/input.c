/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 16:19:31 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/03 14:09:57 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	already_an_edge(t_node *node1, t_node *node2)
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

static int	get_edge(t_graph *graph, char *line)
{
	//char	*name1;
	//char	*name2;
	t_node	*node1;
	t_node	*node2;
	int		i;
	char	**splitted;

	splitted = ft_strsplit(line, '-');
	node1 = give_node_name(graph, splitted[0]);
	node2 = give_node_name(graph, splitted[1]);
	//ft_dprintf(2, "name1: %s, name2: %s\n", name1, name2);
	//ft_dprintf(2, "node1: %s, node2: %s\n", node1->name, node2->name);
	i = -1;
	while (splitted[++i])
		free(splitted[i]);
	free(splitted);
	if (!node1 || !node2)
		//free_all(graph, "Can't add edge and/or unknow node");
		return (-1);
	if (!already_an_edge(node1, node2))
		add_edge(node1, node2);
	return (1);
}

static void	read_edge(t_graph *graph, char *line)
{
	if (ft_strchr(line, '-') == 0)
		return ; //free_all(graph, "Error to read edges");
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
			ft_memdel((void**)&line);
		}
	}
}

int			special_char(t_graph *graph, char **line, int *check)
{
	int a;

	a = 0;
	if (ft_strcmp(*line, "##start") == 0)
		a = 1;
	else if (ft_strcmp(*line, "##end") == 0)
		a = 2;
	ft_memdel((void**)line);
	if (a)
	{
		get_next_line(0, line);
		if (!*line || ft_strchr(*line, '-') || (*line)[0] == '#')
			free_all(graph, "Invalid end or start");
		ft_printf("%s\n", *line);
		a == 1 ? graph->start = graph->nb_sommets : 0;
		a == 2 ? graph->end = graph->nb_sommets : 0;
		(*check)++;
		return (1);
	}
	return (0);
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
		ft_memdel((void**)&line);
		free_all(graph, "Can't get ants number");
	}
	else
	{
		graph->nb_ants = ft_atoi(&line[0]);
		ft_dprintf(2, "nb ants : %d\n", graph->nb_ants);
		ft_printf("%s\n", line);
		ft_memdel((void**)&line);
	}
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (ft_strchr(line, '-'))
			break ;
		if (line[0] == '#')
		{
			if (!special_char(graph, &line, &check))
				continue ;
		}
		i = 0;
		while (line[i] && line[i] != ' ')
			i++;
		line[i] = '\0';
		//ft_dprintf(2, "line cut: %s\n", line);
		push_end(graph, create_node(graph->nb_sommets, line));
		ft_memdel((void**)&line);
		graph->nb_sommets++;
	}
	if (check != 2)
		free_all(graph, "Error on start and/or end");
	if (!line)
		free_all(graph, "No path in input");
	read_edge(graph, line);
	if (graph->start == graph->end || check != 2)
		free_all(graph, "Error input start and/or end");
	ft_printf("\n");
}
