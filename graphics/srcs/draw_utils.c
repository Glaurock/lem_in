/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:35:26 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/19 11:40:24 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_graphics.h"

void	draw_ant(t_env *env, t_point *point)
{
	int x;
	int y;

	x = point->x - ANT_WIDTH;
	while (x++ < point->x + ANT_WIDTH)
	{
		y = point->y - ANT_WIDTH;
		while (y++ < point->y + ANT_WIDTH)
			env->img.data[y * WINDOW_WIDTH + x] = 0xff;
	}
}

void	draw_start_end2(t_env *env, t_point *point)
{
	int x;
	int y;

	x = point->x - START_WIDTH;
	while (x++ < point->x + START_WIDTH)
	{
		y = point->y - START_WIDTH;
		while (y++ < point->y + START_WIDTH)
			env->img.data[y * WINDOW_WIDTH + x] =
			point->end ? 0xff0000 : 0xff00;
	}
}

void	draw_start_end(t_env *env)
{
	t_list_point	*list;

	list = env->head_points;
	while (list)
	{
		if (list->point->start || list->point->end)
			draw_start_end2(env, list->point);
		list = list->next;
	}
}

void	draw_points(t_env *env)
{
	t_list_point	*list;
	int				x;
	int				y;

	list = env->head_points;
	while (list)
	{
		x = list->point->x - POINT_SIZE;
		while (x++ < list->point->x + POINT_SIZE)
		{
			y = list->point->y - POINT_SIZE;
			while (y++ < list->point->y + POINT_SIZE)
				env->img.data[y * WINDOW_WIDTH + x] = 0xffffff;
		}
		list = list->next;
	}
}
