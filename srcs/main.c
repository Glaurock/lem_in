/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:13:04 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/28 14:35:48 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** on cree une fourmi, on la push a la fin de la liste, 
** on met la position a not_free
*/

void		create_ant(t_graph *graph, int *map, t_node **tmp)
{
	t_ant *ant;

	mallcheck(ant = (t_ant*)ft_memalloc(sizeof(t_ant)));
	//check malloc

	graph->tab_ants[graph->index] = ant;
	ant->map = map;
	ant->index = 1;
	(*tmp)->is_free = 0;
	graph->nb_ants--;
	graph->index++;
	if (graph->space)
		ft_printf(" ");
	ft_printf("L%d-%d", graph->index, (*tmp)->number);
	graph->space = 1;
}

void	update_ants(t_graph *graph)
{
	t_node	*tmp;
	int		i;
	t_ant	*ant;

	i = -1;
	while (++i < graph->index)
	{
		//print_path(ant->path);
		ant = graph->tab_ants[i];
		if (!ant)
			continue ;
		tmp = give_node(graph, ant->map[ant->index]);
		//ft_dprintf(2, "tmp :%d\n", tmp->number);
		tmp->is_free = 1;
		ant->index++;
		if (graph->space)
			ft_printf(" ");
		ft_printf("L%d-%d", i + 1, ant->map[ant->index]);
		graph->space = 1;
		if (ant->map[ant->index] == graph->end)
		{
			//ft_dprintf(2, "Arrived!!!\n");
			free(graph->tab_ants[i]);
			graph->tab_ants[i] = NULL;
			graph->arrived++;
		}
		else
		{
			tmp = give_node(graph, ant->map[ant->index]);
			tmp->is_free = 0;
		}
	}
}

int		check_all_tag(t_graph *graph)
{
	t_node *node;

	node = graph->head;
	while (node)
	{
		if (node->number != graph->start && node->number != graph->end && !node->is_a_path)
			return (1);
		node = node->next;
	}
	return (0);
}

/*
** on s'arrete quand on a trouver tous les chemins possibles ou 
** quand la taille du chemin est superieur au chemin mini + nb_ants ( non implementer )
*/

/*
** a chaque tour, on remplit tous les chemins (pas bon ca???)
*/

void	game_loop(t_graph *graph)
{
	int		i;
	//t_node	*path;
	int		*map;
	t_list	*list;
	t_node	*node;
	int		last_dist;

	graph->space = 0;
	ft_dprintf(2, "------Start game loop-----\n\n");
	//fonction update game : pour chaque fourmi, la mettre a la position suivante
	update_ants(graph);
	//ft_dprintf(2, "nb active ants: %d\n", size_ants(graph->list_ants));
	i = 0;
	last_dist = 0;
	list = graph->list_paths;
	while (graph->nb_ants && list)
	{
		map = (int*)(list->content);
		node = give_node(graph, map[1]);
		//ft_dprintf(2, "last_dist: %d, actual_dist: %d\n", last_dist + graph->nb_ants, ft_path_size(path) - 1);
		if (!i)
			create_ant(graph, map, &node);
		else if (node->is_free) //&& last_dist + graph->nb_ants > ft_path_size(path) - 1)
				create_ant(graph, map, &node);
		list = list->next;
		i++;
		//last_dist = ft_path_size(path) - 1;
	}
	//print_graph(graph);
	//ft_dprintf(2, "nb_ants : %d, arrived : %d\n", graph->nb_ants, graph->arrived);
	ft_printf("\n");
}

int		main(int argc, char **argv)
{
	t_graph		*graph;
	int			nb_start;
	int			i;

	mallcheck(graph = (t_graph*)ft_memalloc(sizeof(t_graph)));
	get_input(graph);
	ft_dprintf(2, "start : %d, end: %d\n", graph->start, graph->end);
	mallcheck(graph->tab_path = (t_path*)ft_memalloc(sizeof(t_path) * (graph->nb_ants)));
	find_all_path(graph);
	mallcheck(graph->tab_ants = (t_ant**)ft_memalloc(sizeof(t_ant*) * (graph->nb_ants + 1)));
	nb_start = graph->nb_ants;
	//while (graph->arrived != nb_start)
	//	game_loop(graph);
	//print_graph(graph);
	free(graph->tab_ants);
	//i = -1;
	//while (++i < graph->nb_path)
	//	free_path(graph->tab_path[i].head_path);
	free(graph->tab_path);
	del_graph(graph);
	return (0);
}
