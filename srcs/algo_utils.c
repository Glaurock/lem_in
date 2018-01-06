/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 14:46:24 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 15:10:31 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	save_best_paths(t_graph *graph)
{
	t_list *list;

	ft_lstdel(&graph->list_paths, &free_tab_in_list);
	list = graph->list_tmp;
	while (list)
	{
		ft_lstadd_end(&graph->list_paths,
		ft_lstnew(list->content, list->content_size));
		list = list->next;
	}
}

void	sort_by_size(t_graph *graph)
{
	t_list	*list;
	int		i;
	int		size;
	int		size1;
	int		size2;

	i = -1;
	size = ft_lst_size(graph->list_paths);
	list = graph->list_paths;
	while (++i < size)
	{
		list = graph->list_paths;
		while (list->next)
		{
			size1 = count_path_size((int*)list->content,
			graph->nb_sommets, graph->end);
			size2 = count_path_size((int*)list->next->content,
			graph->nb_sommets, graph->end);
			if (size1 > size2)
				ft_swap_ptr(&(list->content), &(list->next->content));
			list = list->next;
		}
	}
}

void	mark_path(t_graph *graph, int *tab)
{
	int		i;
	t_node	*node;

	i = -1;
	while (++i < graph->nb_sommets)
	{
		if (tab[i] == graph->end)
			return ;
		if (tab[i] != graph->start)
		{
			node = give_node(graph, tab[i]);
			node->is_a_path = 1;
		}
	}
}

void	unmark_path(t_graph *graph, int *tab)
{
	int		i;
	t_node	*node;

	i = -1;
	while (++i < graph->nb_sommets)
	{
		if (tab[i] == graph->end)
			return ;
		if (tab[i] != graph->start)
		{
			node = give_node(graph, tab[i]);
			node->is_a_path = 0;
		}
	}
}

int		count_path_size(int *tab, int size, int end)
{
	int i;

	i = -1;
	while (++i < size)
	{
		if (tab[i] == end)
			return (i);
	}
	return (i);
}
