/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 09:59:29 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/29 17:46:51 by gmonnier         ###   ########.fr       */
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
//	ft_dprintf(2, "min: %d, max: %d\n", env->min_x, env->max_x);
//	ft_dprintf(2, "min: %d, max: %d\n", env->min_y, env->max_y);
}

void	draw_edges(t_env *env, char **line)
{
	t_point		*init;
	t_point		*final;
	char		**splitted;

	do
	{
		if (*line[0] == '\0')
			break ;
		splitted = ft_strsplit(*line, '-');
		init = get_point_in_list(env, splitted[0]);
		final = get_point_in_list(env, splitted[1]);
		draw_line(env, init, final);
		free_splitted(splitted);
		ft_memdel((void**)line);
	}while (get_next_line(0, line) > 0);
}

int	expose_hook(void *param)
{
	t_env *env;
	static int i;

	env = (t_env*)param;
	get_next_time(env->timer);
	if (env->timer->delta >= 1)
	{
//		update_game(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img.img_ptr, 0, 0);
	}
	if (env->timer->timer >= CLOCKS_PER_SEC / 30)
		ft_printf("%d\n", i++);
	return (0);
}

int		main(void)
{
	t_list_point	*list;
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
	get_input(&list, &line);
	env->head_points = list;
	find_min_max(env, list);
	draw_pixels(env, list);
	draw_edges(env, &line);
	mallcheck(env->timer = (t_timer*)ft_memalloc(sizeof(t_timer)));
	timer_init(env->timer);
	mlx_expose_hook(env->win, expose_hook, (void*)env);
	mlx_loop_hook(env->mlx, expose_hook, (void*)env);
	mlx_loop(env->mlx);
}
