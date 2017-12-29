/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 09:37:47 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/29 12:12:42 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	unsigned int i;

	i = 0;
	if (!begin_list)
		return (0);
	while (begin_list && i < nbr)
	{
		begin_list = begin_list->next;
		i++;
	}
	if (i > nbr)
		return (0);
	return (begin_list);
}

void		push_back(t_list **head, t_list *new)
{
	t_list *current;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
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



void		mark_path(t_graph *graph, int *tab)
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
			//graph->tab[WEIGHT][tab[i]] += TAG;
		}
	}
}


void		unmark_path(t_graph *graph, int *tab)
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

void	free_tab_in_list(void *content, size_t n)
{
	free(content);
	(void)n;
}

void		print_list_tmp(t_list *current, int size, int end)
{

	ft_dprintf(2, "print_list_tmp: \n");
	while (current)
	{
		print_tab((int*)current->content, size, end);
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

void		reverse_tab(int *tab, int size)
{
	int tmp;
	int i;

	i = 0;
	while (i < size / 2)
	{
		tmp = tab[size - 1 - i];
		tab[size - i - 1] = tab[i];
		tab[i] = tmp;
		i++;
	}
}
