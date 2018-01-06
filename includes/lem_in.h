/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:11:29 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 15:05:28 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <limits.h>
# include "math.h"

# define WEIGHT 0
# define SEEN 1
# define PATH 2
# define PARENT 0

# define INF 10000

/*
** la liste des liens
*/

typedef struct		s_edge
{
	struct s_node	*links_to;
	struct s_edge	*next;
	int				is_full :2;
	int				w;
	int				wrong_way: 2;
}					t_edge;

typedef struct		s_ant
{
	struct s_ant	*next;
	int				*map;
	int				index;
}					t_ant;

/*
** un noeud du graphe
*/

typedef struct		s_node
{
	int				number;
	char			*name;
	struct s_edge	*edges_l;
	struct s_node	*next;

	//todel
	int				is_free :2;
	int				is_a_path: 2;
}					t_node;

/*
** contient les donnees du graph et un pointeur vers le premier sommet
*/

typedef struct		s_graph
{
	int				start;
	int				end;
	int				nb_ants;
	int				nb_path;
	int				index;
	int				arrived;
	int				nb_sommets;
	int				space: 2;
	struct s_node	*head;
	t_ant			**tab_ants;
	t_list			*list_paths;
	t_list			*list_tmp;
	int				*tab[3];
	int				best;

	t_node			**tab_nodes;
}					t_graph;

t_node				*create_node(int number, char *name);
void				push_end(t_graph *graph, t_node *node);
void				add_edge(t_node *n1, t_node *n2);
void				del_graph(t_graph *graph);
void				print_graph(t_graph *graph);
t_node				*give_node_name(t_graph *graph, char *name);
t_node				*give_node(t_graph *graph, int number);

void				get_input(t_graph *graph);

/* algo */
void			give_weight(t_graph *graph, int start);
int					dijkstra_algo(t_graph *graph, int start, int end);
void				push_path(t_node **head, t_node *path);
void				select_path(t_graph *graph);

int			ft_path_size(t_node *node);
void		ft_reverse_path(t_node **begin_list);
void		print_path(t_node *path);
void		free_path(t_node *path);

/*algo utils*/

int			unreacheable_check(int **tab, int size);
int			check_false(int *tab, int size);
int			check_true(int *tab, int size);

void		reverse_tab(int *tab, int size);

/*algo recursif*/

void	find_all_path(t_graph *graph);

/*fonction basique de liste*/

void		push_back(t_list **head, t_list *new_elem);
t_list	*ft_list_at(t_list *begin_list, unsigned int nbr);

/*divers*/

void	find_nb_path(t_graph *graph);
void	ft_lstadd_end(t_list **head, t_list *elem);
void		mark_path(t_graph *graph, int *tab);
void		unmark_path(t_graph *graph, int *tab);
void	free_tab_in_list(void *content, size_t n);
int			count_path_size(int *tab, int size, int end);

/*ants*/

void		create_ant(t_graph *graph, int *map, t_node **tmp);
void	update_ants(t_graph *graph);

void	free_all(t_graph *graph, char *msg);

/*debug*/
void	aff_graph(t_graph *graph);
void		print_list_tmp(t_list *current, int size, int end);
void		print_tab_previous(t_node **tab_previous, int size);
void		print_weight(int **tab, int size);
void		print_tab(int *tab, int size, int end);

void	transform_list_in_tab(t_graph *graph);

/*new_algo_utils*/

int			calc_nb_lap(t_graph *graph, int code);
int			bfs(t_graph *graph);
void		find_path(t_graph *graph);
void		augment_flow(t_graph *graph);
void		dfs(t_graph *graph, t_node *current, int *path_index);

int		find_negative_path(t_graph *graph);
void	list_edges_in_tmp(t_graph *graph);
void	give_weight_to_edges(t_graph *graph);
t_edge	*give_edge(t_graph *graph, int son, int parent);
void	construct_residual_graph(t_graph *graph);
void	adjust_negative_cycle(t_graph *graph);
void	reset_ways(t_graph *graph);
void	sort_by_size(t_graph *graph);
void	save_best_paths(t_graph *graph);

#endif
