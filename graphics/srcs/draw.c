/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:29:49 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/29 17:13:23 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_graphics.h"

/*
** Algorithme de trace de segment de Bresenham
** copy init point :
** tab[0] = x
** tab[1] = y
** difference
** tab[2] = diff x
** tab[3] = diff y
** incrementation verticale / horizontal
** tab[4] = xinc
** tab[5] = yinc
** tab[6] = cumul d'erreur a chaque tour
*/

void	vertical(t_env *env, int tab[7])
{
	int		i;

	tab[6] = tab[3] / 2;
	i = 0;
	while (++i <= tab[3])
	{
		tab[1] += tab[5];
		tab[6] += tab[2];
		if (tab[6] >= tab[3])
		{
			tab[6] -= tab[3];
			tab[0] += tab[4];
		}
		if (tab[1] < WINDOW_HEIGHT && tab[1] > 0
		&& tab[0] < WINDOW_WIDTH && tab[0] > 0)
			env->img.data[tab[1] * WINDOW_WIDTH + tab[0]] = 0xffffff;
	}
}

void	horizontal(t_env *env, int tab[7])
{
	int		i;

	tab[6] = tab[2] / 2;
	i = 0;
	while (++i <= tab[2])
	{
		tab[0] += tab[4];
		tab[6] += tab[3];
		if (tab[6] >= tab[2])
		{
			tab[6] -= tab[2];
			tab[1] += tab[5];
		}
		if (tab[1] < WINDOW_HEIGHT && tab[1] > 0 && tab[0]
		< WINDOW_WIDTH && tab[0] > 0)
			env->img.data[tab[1] * WINDOW_WIDTH + tab[0]] = 0xffffff;
	}
}

void	draw_line(t_env *env, t_point *ini_point, t_point *final_point)
{
	int		tab[7];
	double	coord_x;
	double	coord_y;
	double	coord_final_x;
	double	coord_final_y;

	coord_x = ini_point->x;
	coord_y = ini_point->y;
	coord_final_x = final_point->x;
	coord_final_y = final_point->y;
	tab[0] = floor(coord_x);
	tab[1] = floor(coord_y);
	tab[2] = floor(coord_final_x - coord_x);
	tab[3] = floor(coord_final_y - coord_y);
	tab[4] = (tab[2] > 0) ? 1 : -1;
	tab[5] = (tab[3] > 0) ? 1 : -1;
	tab[2] = abs(tab[2]);
	tab[3] = abs(tab[3]);
	if (tab[1] < WINDOW_HEIGHT && tab[1] > 0 &&
	tab[0] < WINDOW_WIDTH && tab[0] > 0)
		env->img.data[tab[1] * WINDOW_WIDTH + tab[0]] = 0xffffff;
	if (tab[2] > tab[3])
		horizontal(env, tab);
	else
		vertical(env, tab);
}

void	draw_pixels(t_env *env, t_list_point *list)
{
	double slope_x;
	double slope_y;

	slope_x = get_slope(env->min_x, env->max_x, MARGIN, WINDOW_WIDTH - MARGIN);
	slope_y = get_slope(env->min_y, env->max_y, MARGIN, WINDOW_HEIGHT - MARGIN);
	while (list)
	{
		list->point->x = (int)map(list->point->x, env->min_x, slope_x, MARGIN);
		list->point->y = (int)map(list->point->y, env->min_y, slope_y, MARGIN);
//		ft_dprintf(2, "%d, %d\n", pixel_x, pixel_y);
		if (list->point->y >= 0 && list->point->y < WINDOW_HEIGHT && list->point->x  >= 0 && list->point->y  < WINDOW_WIDTH)
			env->img.data[list->point->y * WINDOW_WIDTH + list->point->x] = 0xffffff;
		list = list->next;
	}
}


