/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:05:48 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/19 11:32:22 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_graphics.h"

void	find_min_max(t_env *env, t_list_point *list)
{
	env->min_x = list->point->x;
	env->max_x = list->point->x;
	env->max_y = list->point->y;
	env->min_y = list->point->y;
	while (list)
	{
		if (list->point->x > env->max_x)
			env->max_x = list->point->x;
		if (list->point->x < env->min_x)
			env->min_x = list->point->x;
		if (list->point->y > env->max_y)
			env->max_y = list->point->y;
		if (list->point->y < env->min_y)
			env->min_y = list->point->y;
		list = list->next;
	}
}

double	get_slope(double min, double max, double new_min, double new_max)
{
	return (1.0 * (new_max - new_min) / (max - min));
}

double	map(double nb, double min, double slope, double new_min)
{
	return (new_min + slope * (nb - min));
}

void	free_splitted(char **splitted)
{
	int i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	ft_memdel((void**)&splitted);
}

void	my_clear_image(t_env *env)
{
	int x;
	int y;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
			env->img.data[y * WINDOW_WIDTH + x] = 0;
	}
}
