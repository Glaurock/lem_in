/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:13:04 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/25 15:46:58 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** sauvegarde temporaire des donnees
** a faire dans un tableau pour la norme
*/

/*void	get_input(void)
{
	char		*line;
	int			nb_sommets;
	int			start;
	int			end;
	int			nb_ants;

	nb_sommets = 0;
	get_next_line(0, &line);
	//ft_dprintf(2, "%s\n", line);
	if (!ft_isdigit(line[0]))
	{
		free(line);
		die("can't get ants number");
	}
	else
	{
		nb_ants = ft_atoi(&line[0]);
		//ft_dprintf(2, "%d\n", nb_ants);
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
			start = nb_sommets;
		}
		if (ft_strcmp(line, "##end") == 0)
		{
			free(line);
			get_next_line(0, &line);
			end = nb_sommets;
		}
		free(line);
		nb_sommets++;
	}
}
*/

void	get_edge(t_graph *graph, char *line)
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
	node1 = give_node(graph, name1);
	node2 = give_node(graph, name2);
	ft_dprintf(2, "name1: %s, name2: %s\n", name1, name2);
	ft_dprintf(2, "node1: %s, node2: %s\n", node1->name, node2->name);
	add_edge(give_node(graph, name1), give_node(graph, name2));
}

void	read_edge(t_graph *graph, char *line)
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

int		main(int argc, char **argv)
{
	t_graph		*graph;

	graph = (t_graph*)ft_memalloc(sizeof(t_graph));
	get_input(graph);
	print_graph(graph);
	del_graph(graph);
	return (0);
}
//ft_dprintf(2, "start: %d, end: %d, nb_ants:%d\n", graph->start, graph->end, graph->nb_ants);
