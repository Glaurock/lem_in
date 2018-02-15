/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fauconfan <fauconfan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 18:01:16 by fauconfan         #+#    #+#             */
/*   Updated: 2018/02/15 18:01:40 by fauconfan        ###   ########.fr       */
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
