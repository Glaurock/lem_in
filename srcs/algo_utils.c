/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 14:46:24 by gmonnier          #+#    #+#             */
/*   Updated: 2017/12/29 10:35:20 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_weight(int **tab, int size)
{
	int i;

	ft_dprintf(2, "\nprint_tab :\n");
	i = -1;
	while (++i < size)
	{
		ft_dprintf(2, "weight[%d]: %-3d || %s\n", i, tab[WEIGHT][i], tab[SEEN][i] == true ? "true" : "false" );
	}
}

int			unreacheable_check(int **tab, int size)
{
	int i;
	int check;

	i = -1;
	check = 0;
	while (++i < size)
	{
		if (tab[SEEN][i] == false && tab[WEIGHT][i] != -1)
			check = 1;
	}
	return (check);
}

int			check_false(int *tab, int size)
{
	int count;
	int i;

	count = 0;
	i = -1;
	while (++i < size)
	{
		if (tab[i] == false)
			count++;
	}
	return (count == 1 ? 0 : 1);
}

int			check_true(int *tab, int size)
{
	int i;

	i = 0;
	while (++i < size)
	{
		if (tab[i] == true)
			return (0);
	}
	return (1);
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
