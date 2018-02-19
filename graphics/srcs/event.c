/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:13:53 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/19 11:17:01 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_graphics.h"

int		expose_hook(void *param)
{
	t_env	*env;
	char	*line;

	env = (t_env*)param;
	get_next_time(env->timer);
	if (env->timer->timer >= CLOCKS_PER_SEC / TIMER)
	{
		if (get_next_line(0, &line) > 0)
		{
			my_clear_image(env);
			update_game(env, line);
			reset_timer(env->timer);
			mlx_put_image_to_window(env->mlx, env->win, env->img.img_ptr, 0, 0);
			ft_memdel((void**)&line);
		}
		else
			exit(EXIT_SUCCESS);
	}
	return (0);
}

int		exit_hook(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
}
