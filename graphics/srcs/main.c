/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 09:59:29 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/30 16:30:20 by gmonnier         ###   ########.fr       */
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

void	update_game(t_env *env, char *line)
{
	char	**splitted;
	char	**splitted2;
	int		i;
	t_point	*point;

	splitted = ft_strsplit(line, ' ');
	i = 0;
	draw_edges(env);
	draw_points(env);
	while (splitted[i])
	{
		splitted2 = ft_strsplit(splitted[i], '-');
		point = get_point_in_list(env, splitted2[1]);
//		ft_dprintf(2, "%d, %d\n", point->x, point->y);
		draw_ant(env, point);
		free_splitted(splitted2);
		i++;
	}
	draw_start_end(env);
	free_splitted(splitted);
}

int		main(void)
{
	t_list_point	*list;
	t_list_edges	*l_edges;
	char			*line;
	t_env			*env;

	env = NULL;
	mallcheck(env = (t_env*)ft_memalloc(sizeof(t_env)));
	mallcheck(env->mlx = mlx_init());
	mallcheck(env->win = mlx_new_window(env->mlx, WINDOW_WIDTH,
		WINDOW_HEIGHT, "lem_in"));
	mallcheck(env->img.img_ptr = mlx_new_image(env->mlx, WINDOW_WIDTH,
		WINDOW_HEIGHT));
	env->img.data = (int*)mlx_get_data_addr(env->img.img_ptr, &env->img.bpp,
		&env->img.size_l, &env->img.endian);
	list = NULL;
	line = NULL;
	l_edges = NULL;
	env->head_edges = l_edges;
	env->head_points = list;
	get_input(env, &line);
	list = env->head_points;

	find_min_max(env, list);
	give_coord(env);
	draw_edges(env);
	draw_points(env);
	draw_start_end(env);

	mallcheck(env->timer = (t_timer*)ft_memalloc(sizeof(t_timer)));
	timer_init(env->timer);

	mlx_put_image_to_window(env->mlx, env->win, env->img.img_ptr, 0, 0);
	mlx_hook(env->win, 17, 0, exit_hook, (void*)env);
	mlx_expose_hook(env->win, expose_hook, (void*)env);
	mlx_loop_hook(env->mlx, expose_hook, (void*)env);
	mlx_loop(env->mlx);
}
