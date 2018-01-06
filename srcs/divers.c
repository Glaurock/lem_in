/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 09:37:47 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/06 15:15:14 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_list_tmp(t_list *current, int size, int end)
{
	ft_dprintf(2, "print_list_tmp: \n");
	while (current)
	{
		print_tab((int*)current->content, size, end);
		current = current->next;
	}
}

void		print_weight(int **tab, int size)
{
	int i;

	ft_dprintf(2, "\nprint_tab :\n");
	i = -1;
	while (++i < size)
		ft_dprintf(2, "weight[%d]: %-3d || path: %d\n", i,
		tab[WEIGHT][i], tab[PATH][i]);
}

void		print_tab(int *tab, int size, int end)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		ft_dprintf(2, "(%d) || ", tab[i]);
		if (tab[i] == end)
		{
			ft_dprintf(2, "\n");
			return ;
		}
	}
	ft_dprintf(2, "\n");
}
