/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_graphics.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:00:03 by gmonnier          #+#    #+#             */
/*   Updated: 2018/01/29 17:14:18 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_GRAPHICS_H
# define LEM_IN_GRAPHICS_H

# include <limits.h>
# include "libft.h"
# include "math.h"
# include "mlx.h"
# include "/System/Library/Frameworks/Tk.framework/Versions/8.4/Headers/X11/X.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MARGIN 25

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_list_point
{
	struct s_list_point	*next;
	char				*name;
	t_point				*point;
}						t_list_point;

typedef struct			s_img
{
	void				*img_ptr;
	int					*data;
	int					size_l;
	int					bpp;
	int					endian;
}						t_img;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_img				img;
	t_list_point		*head_points;
	int					min_x;
	int					max_x;
	int					min_y;
	int					max_y;
}						t_env;

void	draw_line(t_env *env, t_point *ini_point, t_point *final_point);
double	get_slope(double min, double max, double new_min, double new_max);
double	map(double nb, double min, double slope, double new_min);
t_point	*get_point_in_list(t_env *env, char *name);
void	free_splitted(char **splitted);
void	draw_pixels(t_env *env, t_list_point *list);
void	get_input(t_list_point **list, char **line);
#endif
