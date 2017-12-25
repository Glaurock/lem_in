/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:11:29 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/25 22:51:16 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define WEIGHT 0
# define SEEN 1

typedef enum
{
	false,
	true
}				e_bool;

/*
** struct ants, qui contient le chemin que la fourmi doit emprunter
*/

typedef struct		s_ant
{
	struct s_ant	*next;
	struct s_node	*path;
	struct s_node	*current;
}					t_ant;

/*
** la liste des liens
*/

typedef struct		s_edge
{
	struct s_node	*links_to;
	struct s_edge	*next;
}					t_edge;

/*
** un noeud du graphe
*/

typedef struct		s_node
{
	int				number;
	char			*name;
	int				is_free :2;
	int				is_a_path :2;
	struct s_edge	*edges_l;
	struct s_node	*next;
}					t_node;

/*
** contient les donnees du graph et un pointeur vers le premier sommet
*/

typedef struct		s_graph
{
	int				start;
	int				end;
	int				nb_ants;
	int				nb_sommets;
	struct s_node	*head;
	struct s_ant	*list_ants;
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
t_node				*dijkstra_algo(t_graph *graph, int start, int end);


int			ft_path_size(t_node *node);
void		ft_reverse_path(t_node **begin_list);
void		print_path(t_node *path);

#endif
