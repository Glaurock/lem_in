/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:05:48 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/29 17:13:39 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_graphics.h"

double	get_slope(double min, double max, double new_min, double new_max)
{
	return (1.0 * (new_max - new_min) / (max - min));
}

double	map(double nb, double min, double slope, double new_min)
{
	return (new_min + slope * (nb - min));
}

t_point	*get_point_in_list(t_env *env, char *name)
{
	t_list_point *list;

	list = env->head_points;
	while (list)
	{
		if (ft_strcmp(list->name, name) == 0)
			return (list->point);
		list = list->next;
	}
	return (NULL);
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
