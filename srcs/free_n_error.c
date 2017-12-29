/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:20:51 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/29 14:33:35 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_all(t_graph *graph, char *msg)
{
	if (graph)
	{
		if (graph->tab_ants)
			ft_memdel((void**)&graph->tab_ants);
		del_graph(graph);
	}
	if (msg)
		die(msg);
}
