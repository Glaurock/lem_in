/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:20:51 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 11:54:35 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_all(t_graph *graph, char *msg)
{
	if (graph)
	{
		ft_memdel((void**)&graph->tab_ants);
		ft_memdel((void**)&graph->tab[WEIGHT]);
		ft_memdel((void**)&graph->tab[PATH]);
		ft_memdel((void**)&graph->tab[SEEN]);
		ft_memdel((void**)&graph->tab_nodes);
		ft_lstdel(&graph->list_tmp, &free_tab_in_list);
		ft_lstdel(&graph->list_paths, &free_tab_in_list);
		del_graph(graph);
	}
	if (msg)
		die(msg);
}

void	free_tab_in_list(void *content, size_t n)
{
	free(content);
	(void)n;
}
