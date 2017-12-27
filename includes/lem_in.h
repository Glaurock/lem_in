/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:11:29 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/27 18:53:34 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define WEIGHT 0
# define SEEN 1
# define PATH 2

/*
** la liste des liens
*/

typedef struct		s_edge
{
	struct s_node	*links_to;
	struct s_edge	*next;
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
	int				is_free :2;
	int				is_a_path: 2;
	struct s_edge	*edges_l;
	struct s_node	*next;
}					t_node;

typedef struct		s_path
{
	struct s_node	*head_path;
	struct s_path	*next;
}					t_path;

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
	struct s_path	*tab_path;
	//struct s_path	*list_paths;
	t_list			*list_paths;
	t_list			*list_tmp;
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
void		print_tab_previous(t_node **tab_previous, int size);
void		print_weight(int **tab, int size);

void		reverse_tab(int *tab, int size);
#endif
