/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:18:48 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/24 23:14:21 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_graph			*new_graph(int nb_sommets)
{
	int			i;
	t_graph		*elem;

	elem = (t_graph*)malloc(sizeof(t_graph));
	//check malloc
	elem->nb_sommets = nb_sommets;

	elem->tab_links = (t_links*)malloc(sizeof(t_links) * nb_sommets);
	//check malloc
	i = -1;
	while (++i < nb_sommets)
		elem->tab_links[i].head = NULL;
	return (elem);
}

t_node				*add_node(int value, char *name)
{
	t_node		*new;

	new = (t_node*)malloc(sizeof(t_node));
	//check malloc

	new->value = value;
	new->name = ft_strdup(name);
	new->next = NULL;
	return (new);
}

void				add_edge(t_graph *graph, t_node *n1, t_node *n2)
{
	//t_node		*new;

	n1->next = graph->tab_links[n2->value].head;
	graph->tab_links[n2->value].head = n1;
	/*lien entre src -> dest, et dest <- src*/
	//new = add_node(dest);
	n2->next = graph->tab_links[n1->value].head;
	graph->tab_links[n1->value].head = n2;

	//new = add_node(src);
}

void				del_graph(t_graph *graph)
{
	int			i;
	t_node		*node;
	t_node		*tmp;

	if (!graph)
		return ;
	if (graph->tab_links)
	{
		i = -1;
		while (++i < graph->nb_sommets)
		{
			node = graph->tab_links[i].head;
			while (node)
			{
				tmp = node;
				node = node->next;
				free(tmp->name);
				free(tmp);
			}
		}
		free(graph->tab_links);
	}
	free(graph);
}

void				print_graph(t_graph *graph)
{
	int		i;
	t_node	*node;

	i = -1;
	while (++i < graph->nb_sommets)
	{
		node = graph->tab_links[i].head;
		if (node)
			ft_printf("Node : (%d) : %-10s", i, node->name);
		while (node)
		{
			ft_printf("{%d || ", node->value);
			ft_printf("%s}, ", node->name);
			node = node->next;
		}
		ft_printf("NULL\n");
	}
}
