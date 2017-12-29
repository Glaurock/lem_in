/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 09:22:28 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/28 19:19:49 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


void		depth_first_search(t_graph *graph, t_node *current, int **tab, int *path_index)
{
	t_edge	*edge;
	//int		*copy_tab;

	print_weight(tab, graph->nb_sommets);
	tab[SEEN][current->number] = true;
	tab[PATH][*path_index] = current->number;
	(*path_index)++;
	if (current->number == graph->start)
	{
		ft_dprintf(2, "Shortest path find: ");
		for (int i = 0; i < *path_index; i++)
			ft_dprintf(2, "%d | ", tab[PATH][i]);
		ft_dprintf(2, "\n");
		//mallcheck(copy_tab = (int*)ft_memalloc(sizeof(int) * graph->nb_sommets));
		//ft_memcpy(copy_tab, tab[PATH], sizeof(int) * graph->nb_sommets);
		ft_lstadd(&graph->list_tmp, ft_lstnew((void*)tab[PATH], sizeof(int) * graph->nb_sommets));
		reverse_tab((int*)(graph->list_tmp->content), *path_index);
	}
	else
	{
	//ft_dprintf(2, "current : (%d)\n", current->number);
		edge = current->edges_l;
		while (edge)
		{
			//if (tab[edge->links_to->number] == tab[current->number] - 1)
			//{
				//push_node_on_path(&path, edge->links_to);
			if (tab[WEIGHT][edge->links_to->number] == tab[WEIGHT][current->number] - 1)
				depth_first_search(graph, edge->links_to, tab, path_index);
			//}
			edge = edge->next;
		}
	}
	(*path_index)--;
	tab[SEEN][current->number] = false;
	//push_path_on_list_path(&graph->list_paths, path);
	//print_weight(tab, graph->nb_sommets);
	if (check_true(tab[SEEN], graph->nb_sommets))
	{
		ft_dprintf(2, "finish\n");
	}
}

void		mark_path(t_graph *graph, int *tab)
{
	int		i;

	i = -1;
	while (++i < graph->nb_sommets)
	{
		if (tab[i] == graph->end)
		{
			ENDL
			return ;
		}
		if (tab[i] != graph->start)
			graph->tab[WEIGHT][tab[i]] += 5000;
	}
	ENDL
}


void		unmark_path(t_graph *graph, int *tab)
{
	int		i;

	i = -1;
	while (++i < graph->nb_sommets)
	{
		if (tab[i] == graph->end)
		{
			ENDL
			return ;
		}
		if (tab[i] != graph->start)
			graph->tab[WEIGHT][tab[i]] -= 5000;
	}
}

void	free_tab_in_list(void *content, size_t n)
{
	free(content);
	(void)n;
}

void		print_list_tmp(t_list *current, int size)
{

	ft_dprintf(2, "print_list_tmp: \n");
	while (current)
	{
		print_tab((int*)current->content, size);
		current = current->next;
	}
}

int			count_path_size(int *tab, int size, int end)
{
	int i;

	i = -1;
	while (++i < size)
	{
		if (tab[i] == end)
			return (i + 1);
	}
	return (i);
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
	ft_memset(graph->tab[SEEN], false, sizeof(int) * graph->nb_sommets);
	depth_first_search(graph, give_node(graph, graph->end), graph->tab, &path_index);
	save_best_ptr = NULL;
	save_best = NULL;
	//ft_dprintf(2, "size list_tmp: %d\n", ft_lst_size(graph->list_tmp));
	//ft_dprintf(2, "test size: %d\n", count_path_size((int*)graph->list_tmp->content, graph->nb_sommets, graph->end));

	if (graph->list_tmp == NULL)
		return (NULL);
	//ENDL;
	if (ft_lst_size(graph->list_tmp) == 1)
	{
		save_best = ft_lstnew(graph->list_tmp->content, graph->list_tmp->content_size);
		ft_lstdel(&graph->list_tmp, &free_tab_in_list);
		return (save_best);
	}
	else
	{
		save_list_tmp = graph->list_tmp;
		current = graph->list_tmp;
		graph->list_tmp = NULL;
		while (current)
		{
			mark_path(graph, (int*)current->content);
			print_list_tmp(save_list_tmp, graph->nb_sommets);
			test = select_best_path(graph);
			if (!test)
				size = MAX_SIZE;
			else
				size = count_path_size((int*)test->content, graph->nb_sommets, graph->end);
			ft_dprintf(2, "size path de test: %d\n", size);
			if (size < min_size)
			{
				min_size = size;
				save_best_ptr = test;
			}
			unmark_path(graph, (int*)current->content);
			current = current->next;
		}
		if (save_best_ptr)
			save_best = ft_lstnew(save_best_ptr->content, save_best_ptr->content_size);
		ft_lstdel(&test, &free_tab_in_list);
		ft_lstdel(&save_list_tmp, &free_tab_in_list);
		return (save_best);
	}
}

void	find_nb_path(t_graph *graph)
{
	int		nb;
	int		nb2;
	t_node	*current;
	t_edge	*edge;

	nb = 0;
	current = give_node(graph, graph->start);
	edge = current->edges_l;
	while (edge)
	{
		nb++;
		edge = edge->next;
	}
	nb2 = 0;
	current = give_node(graph, graph->end);
	edge = current->edges_l;
	while (edge)
	{
		nb2++;
		edge = edge->next;
	}
	graph->nb_path = nb > nb2 ? nb2 : nb;
}

void	ft_lstadd_end(t_list **head, t_list *elem)
{
	t_list *current;

	if (!head || !elem)
		return ;
	if (!*head)
		*head = elem;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = elem;
	}
}

void	find_all_path(t_graph *graph)
{
	//t_node	*path;
	int		i;
	t_list	*list;

	find_nb_path(graph);
	ft_dprintf(2, "nb_path: %d\n", graph->nb_path);
	i = 0;
	mallcheck(graph->tab[PATH] = (int*)ft_memalloc(sizeof(int) * graph->nb_sommets));
	give_weight(graph, graph->start, graph->end);
	while (i < graph->nb_path)
	{
		list = select_best_path(graph);
		ft_dprintf(2, "Chemin trouve: ");
		print_tab((int*)list->content, graph->nb_sommets);
		ft_lstadd_end(&graph->list_paths, list);
		mark_path(graph, (int*)list->content);
		i++;
	}
	list = graph->list_paths;
	while (list)
	{
		print_tab((int*)list->content, graph->nb_sommets);
		list = list->next;
	}
}
