/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 16:22:01 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/27 19:38:36 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		get_index_min_weight(int **tab, int size)
{
	int i;
	int min;
	int ret;
	int first;

	i = -1;
	ret = 0;
	first = 1;
	while (++i < size)
	{
		if (first && tab[SEEN][i] == false && tab[WEIGHT][i] >= 0)
		{
			min = tab[WEIGHT][i];
			first = 0;
		}
		if (!first && tab[WEIGHT][i] <= min && tab[WEIGHT][i] >= 0 && tab[SEEN][i] == false)
		{
			ret = i;
			min = tab[WEIGHT][i];
		}
	}
	return (ret);
}

void		del_first_path(t_node **tab_previous, int index)
{
	t_node *tmp;

	tmp = tab_previous[index];
	tab_previous[index] = tab_previous[index]->next;
	free(tmp);
	print_tab_previous(tab_previous, 6);
}

void		print_all_paths(t_graph *graph)
{
	t_list	*list;
	int		i;

	list = graph->list_paths;
	while (list)
	{
		i = -1;
		while (++i < graph->nb_sommets)
		{
			ft_dprintf(2, "%d --> ", ((int*)(list->content))[i]);
		}
		ft_dprintf(2, "\n");
		list = list->next;
	}
}

void		reverse_tab(int *tab, int size)
{
	int i;
	int tmp;

	i = 0;
	while (i < size / 2)
	{
		tmp = tab[size - i - 1];
		tab[size - i - 1] = tab[i];
		tab[i] = tmp;
		i++;
	}
}


void		depth_first_search(t_graph *graph, t_node *current, int **tab, int *path_index)
{
	t_edge	*edge;
	//int		*copy_tab;

	tab[SEEN][current->number] = true;
	tab[PATH][*path_index] = current->number;
	(*path_index)++;

	if (current->number == graph->start)
	{
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
}

int			dijkstra_algo(t_graph *graph, int start, int end)
{
	int		*tab[3]; // ajout tab for path ici
	t_node	**tab_previous;
	int		i;
	t_node	*current;
	t_edge	*edge;
	int		i_son;
	int		i_father;
	//t_node	*path;
	t_node	*tmp_check;
	//t_path	*new_path;

	ft_dprintf(2, "--------Start aglo--------\n\n");
	mallcheck(tab[SEEN] = (int*)malloc(sizeof(int) * graph->nb_sommets));
	mallcheck(tab[WEIGHT] = (int*)malloc(sizeof(int) * graph->nb_sommets));
	mallcheck(tab[PATH] = (int*)malloc(sizeof(int) * graph->nb_sommets));
	mallcheck(tab_previous = (t_node**)malloc(sizeof(t_node*) * graph->nb_sommets));

	i = -1;
	while (++i < graph->nb_sommets)
	{
		tab[WEIGHT][i] = -1;
		tab[SEEN][i] = false;
		tab_previous[i] = NULL;
	}
	tab[WEIGHT][start] = 0;

	/* debut algo */
	/* tant que le noeud ayant le poids le plus faible n'est pas end */

	i_father = get_index_min_weight(tab, graph->nb_sommets);
	i = 0;
	while (check_false(tab[SEEN], graph->nb_sommets))
	{
		//ft_dprintf(2, "i_father : %d\n", i_father);
		tab[SEEN][i_father] = true;

		// on parcours les fils du noeud

		current = give_node(graph, i_father);

		if (current->is_a_path)
			tab[WEIGHT][i_father] += 5000;

		//ft_dprintf(2, "current: %d\n", current->number);
		edge = current->edges_l;
		//ft_dprintf(2, "edges: %d\n", current->edges_l->links_to->number);
		while (edge)
		{
			i_son = edge->links_to->number;
			//ft_dprintf(2, "i_son : %d\n", i_son);
			// si le noeud n'a pas encore ete parcouru 
			//{
				if (tab[WEIGHT][i_son] == -1 ||
				(tab[WEIGHT][i_father] + 1 <= tab[WEIGHT][i_son]))
				{
					if (tab[SEEN][i_son] == false)
						tab[WEIGHT][i_son] = tab[WEIGHT][i_father] + 1;
					push_path(&tab_previous[i_son], current);
				}
			//}
			edge = edge->next;
		}
		// check for unreacheable nodes
		i_father = get_index_min_weight(tab, graph->nb_sommets);
		if (!unreacheable_check(tab, graph->nb_sommets))
		{
			free(tab[WEIGHT]);
			free(tab[SEEN]);
			free(tab[PATH]);
			return (0);
		}
	}
	//print_weight(tab, graph->nb_sommets);
	//print_tab_previous(tab_previous, graph->nb_sommets);

	/* on retrouve le chemin a emprunter */

	/* traite tab_previous pour obtenir le chemin : on stock la liste des chemins dans list_paths*/
	//list_paths = NULL;
	//get_path(&list_paths, tab_previous, start, end);
	//print_all_paths(list_paths);

	i = -1;
	while (++i < graph->nb_sommets)
		tab[SEEN][i] = false;
	
	int path_index;
	path_index = 0;
	current = give_node(graph, graph->end);
	depth_first_search(graph, current, tab, &path_index);
	select_path(graph);

	print_all_paths(graph);

//print_all_paths(graph->list_paths);

	/*tmp_check = give_node(graph, path->next->number);
	if (tmp_check->is_a_path)
	{
		free_path(path);
		return (NULL);
	}*/
	//print_path(path);
	free(tab[WEIGHT]);
	free(tab[SEEN]);
	free(tab[PATH]);
	return (1);
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

/*
** on cherche des chemins sans points commun
*/

void		select_path(t_graph *graph)
{
	int		*tab_count;
	t_list	*list;

	mallcheck(tab_count = (int*)ft_memalloc(sizeof(int) * graph->nb_sommets));
	list = graph->list_tmp;
	if (ft_lst_size(list) >= 3)
	{
		
	}
	push_back(&graph->list_paths, ft_lstnew(graph->list_tmp->content, sizeof(int*) * graph->nb_sommets));
	free(tab_count);
}
