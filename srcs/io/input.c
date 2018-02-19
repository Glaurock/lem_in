/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fauconfan <fauconfan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 16:19:31 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/19 10:32:07 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			special_char(t_graph *graph, char **line, int *check)
{
	int a;

	a = 0;
	if (ft_strcmp(*line, "##start") == 0)
		a = 1;
	else if (ft_strcmp(*line, "##end") == 0)
		a = 2;
	else if (ft_strncmp(*line, "##", 2) == 0)
		return (-1);
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
	return (2);
}

static void	init(t_graph *graph)
{
	char *line;

	if (get_next_line(0, &line) <= 0)
		free_all(graph, "Can't read input and/or empty input");
	if (*line == 0 || ft_strisdigit(line) == 0)
	{
		ft_memdel((void**)&line);
		free_all(graph, "Can't get ants number");
	}
	else
	{
		graph->nb_ants = ft_atoi(&line[0]);
		ft_printf("%s\n", line);
		ft_memdel((void**)&line);
	}
}

static void	fatal_errors(t_graph *graph, char *line, int check)
{
	if (check != 2)
		free_all(graph, "Error on start and/or end");
	if (!line)
		free_all(graph, "No path in input");
	read_edge(graph, line);
	if (graph->start == graph->end || check != 2)
		free_all(graph, "Error input start and/or end");
}

static void	new_node(t_graph *graph, char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	line[i] = '\0';
	push_end(graph, create_node(graph->nb_sommets, line));
	ft_memdel((void**)&line);
}

/*
**	Reading input from stdin
*/

void		get_input(t_graph *graph)
{
	char	*line;
	int		check;
	int		ret;

	check = 0;
	init(graph);
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (ft_strchr(line, '-'))
			break ;
		ret = 0;
		if (line[0] == '#')
			ret = special_char(graph, &line, &check);
		if (ret == 2)
			continue ;
		else if (ret == -1)
			break ;
		new_node(graph, line);
		graph->nb_sommets++;
	}
	fatal_errors(graph, line, check);
	ft_printf("\n");
}
