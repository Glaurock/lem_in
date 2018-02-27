/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 18:01:16 by fauconfan         #+#    #+#             */
/*   Updated: 2018/02/27 15:42:32 by jpriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	handle_following_special_char_loop(
					t_graph *graph,
					char **line,
					int a,
					int *check)
{
	while (1)
	{
		if (get_next_line(0, line) <= 0)
			free_all(graph, "Invalid end or start");
		ft_printf("%s\n", *line);
		if ((*line == 0) || ft_strchr(*line, '-') ||
			((*line)[0] == '#' && (*line)[1] == '#'))
			free_all(graph, "Invalid following commands");
		else if ((*line)[0] == '#')
			continue ;
		a == 1 ? graph->start = graph->nb_sommets : 0;
		a == 2 ? graph->end = graph->nb_sommets : 0;
		(*check)++;
		return ;
	}
}
