/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:13:04 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/25 00:51:59 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	die(char *msg)
{
	ft_dprintf(2, "%s\n", msg);
	exit(EXIT_FAILURE);
}

int		main(int argc, char **argv)
{
	t_graph		*graph;
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
	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		ft_dprintf(2, "line dans boucle: %s\n", line);
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
	if (!line)
		exit(EXIT_FAILURE);
	graph = new_graph(nb_sommets);
	graph->start = start;
	graph->end = end;
	graph->nb_ants = nb_ants;
	ft_dprintf(2, "start: %d, end: %d, nb_ants:%d\n", graph->start, graph->end, graph->nb_ants);
	add_edge(graph, ft_atoi(&line[0]), ft_atoi(&line[2]));
	free(line);
	while (get_next_line(0, &line) > 0)
	{
		add_edge(graph, ft_atoi(&line[0]), ft_atoi(&line[2]));
		free(line);
	}
	print_graph(graph);
	del_graph(graph);
	return (0);
}
