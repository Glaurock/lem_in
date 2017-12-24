/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 22:11:29 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/24 23:17:10 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef enum
{
	false,
	true
}				e_bool;

/*
** un noeud du graphe
*/

typedef struct		s_node
{
	int				value;
	char			*name;
	struct s_node	*next;
}					t_node;

/*
** Liste d'adjacence
*/

typedef struct		s_links
{
	t_node			*head;
}					t_links;

typedef struct		s_graph
{
	int				nb_sommets;
	t_links			*tab_links;
}					t_graph;

t_graph				*new_graph(int nb_sommets);
t_node				*add_node(int value, char *name);
//void				add_edge(t_graph *graph, int src, int dest);
void				add_edge(t_graph *graph, t_node *n1, t_node *n2);
void				del_graph(t_graph *graph);
void				print_graph(t_graph *graph);

#endif
