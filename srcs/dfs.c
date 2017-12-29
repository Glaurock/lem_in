/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 09:22:28 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/29 13:46:29 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*int			give_min_weight(int **tab, t_edge *edge)
{
	int min;

	min = MAX_SIZE;
	while (edge)
	{
		if (tab[WEIGHT][edge->links_to->number] < min && tab[SEEN][edge->links_to->number] == false)
			min = tab[WEIGHT][edge->links_to->number];
		edge = edge->next;
	}
	return (min);
}
*/
void		depth_first_search(t_graph *graph, t_node *current, int **tab, int *path_index)
{
	t_edge	*edge;
	int		min_weight;
	//int		*copy_tab;

	//print_weight(tab, graph->nb_sommets);
	tab[SEEN][current->number] = true;
	tab[PATH][*path_index] = current->number;
	(*path_index)++;
	if (current->number == graph->end)
	{
		//ft_dprintf(2, "Shortest path find: ");
		//for (int i = 0; i < *path_index; i++)
		//	ft_dprintf(2, "%d | ", tab[PATH][i]);
		//ft_dprintf(2, "\n");
		//mallcheck(copy_tab = (int*)ft_memalloc(sizeof(int) * graph->nb_sommets));
		//ft_memcpy(copy_tab, tab[PATH], sizeof(int) * graph->nb_sommets);
		ft_lstadd(&graph->list_tmp, ft_lstnew((void*)tab[PATH], sizeof(int) * graph->nb_sommets));
		//reverse_tab((int*)(graph->list_tmp->content), *path_index);
	}
	else
	{
		//ft_dprintf(2, "current : (%d)\n", current->number);
		edge = current->edges_l;
		//min_weight = give_min_weight(tab, edge);
		//ft_dprintf(2, "Min_weight: %d\n", min_weight);
		while (edge)
		{
			//if (min_weight >= TAG)
			//	break ;
			//if (tab[WEIGHT][edge->links_to->number] == tab[WEIGHT][current->number] + 1 && tab[SEEN][edge->links_to->number] == false && tab[WEIGHT][edge->links_to->number] < TAG)
			//if (tab[WEIGHT][edge->links_to->number] == min_weight && tab[SEEN][edge->links_to->number] == false)
			if (tab[WEIGHT][edge->links_to->number] == tab[WEIGHT][current->number] + 1)
				depth_first_search(graph, edge->links_to, tab, path_index);
			edge = edge->next;
		}
	}
	(*path_index)--;
	tab[SEEN][current->number] = false;
	//push_path_on_list_path(&graph->list_paths, path);
	//print_weight(tab, graph->nb_sommets);
	//if (check_true(tab[SEEN], graph->nb_sommets))
//	{
//		ft_dprintf(2, "finish\n");
//	}
}

t_list		*select_best_path(t_graph *graph)
{
	int		path_index;
	t_list	*current;
	int		min_size;
	t_list	*test;
	t_list	*save_best;
	t_list	*save_best_ptr;
	int		size;
	t_list	*save_list_tmp;

	min_size = MAX_SIZE;
	path_index = 0;
	//ft_memset(graph->tab[SEEN], false, sizeof(int) * graph->nb_sommets);

	give_weight(graph, graph->start, graph->end);

	depth_first_search(graph, give_node(graph, graph->start), graph->tab, &path_index);
	save_best = NULL;
	//ft_dprintf(2, "size list_tmp: %d\n", ft_lst_size(graph->list_tmp));
	//ft_dprintf(2, "test size: %d\n", count_path_size((int*)graph->list_tmp->content, graph->nb_sommets, graph->end));

	if (graph->list_tmp == NULL)
		return (NULL);
	//ENDL;
	if (ft_lst_size(graph->list_tmp) == 1)
	{
		save_best = ft_lstnew(graph->list_tmp->content, graph->list_tmp->content_size);
		ft_dprintf(2, "Chemin trouve :		");
		print_tab((int*)save_best->content, graph->nb_sommets, graph->end);
		ft_lstdel(&graph->list_tmp, &free_tab_in_list);
		return (save_best);
	}
	else
	{
		save_list_tmp = graph->list_tmp;
		current = graph->list_tmp;
		graph->list_tmp = NULL;
		save_best_ptr = current;
		while (current)
		{
			mark_path(graph, (int*)current->content);
			ft_dprintf(2, "Chemin teste: ");
			print_tab((int*)current->content, graph->nb_sommets, graph->end);
			//print_list_tmp(save_list_tmp, graph->nb_sommets, graph->end);
			//ENDL
			test = select_best_path(graph);
			if (!test)
				size = MAX_SIZE;
			else
				size = count_path_size((int*)test->content, graph->nb_sommets, graph->end);
			//ft_dprintf(2, "size path de test: %d\n", size);
			if (size < min_size && size > 0)
			{
				min_size = size;
				save_best_ptr = current;
			}
			unmark_path(graph, (int*)current->content);
			current = current->next;
			ft_lstdel(&test, &free_tab_in_list);
		}
		save_best = ft_lstnew(save_best_ptr->content, save_best_ptr->content_size);
		ft_lstdel(&save_list_tmp, &free_tab_in_list);
		//ENDL
		return (save_best);
	}
}

/*
** on s'arrete quand on a trouver assez de chemin (i) ou quand plus de chemin dispo (!list)
*/

void	find_all_path(t_graph *graph)
{
	//t_node	*path;
	int		i;
	t_list	*list;

	find_nb_path(graph);
	ft_dprintf(2, "nb_path: %d\n", graph->nb_path);
	i = 0;
	mallcheck(graph->tab[PATH] = (int*)ft_memalloc(sizeof(int) * graph->nb_sommets));
	//give_weight(graph, graph->start, graph->end);
	while (i < graph->nb_path)
	{
		list = select_best_path(graph);
		//ft_dprintf(2, "Chemin trouve: ");
		if (list)
		{
			//print_tab((int*)list->content, graph->nb_sommets, graph->end);
			ft_lstadd_end(&graph->list_paths, list);
			mark_path(graph, (int*)list->content);
		}
		else
			break ;
		i++;
	}
	ft_dprintf(2, "i: %d\n", i);
	list = graph->list_paths;
	ft_dprintf(2, "Liste des chemins trouves: ");
	while (list)
	{
		print_tab((int*)list->content, graph->nb_sommets, graph->end);
		list = list->next;
	}
}
