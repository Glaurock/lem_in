/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_graphics.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:00:03 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/20 11:20:31 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_GRAPHICS_H
# define LEM_IN_GRAPHICS_H

# include <limits.h>
# include "libft.h"
# include <math.h>
# include <mlx.h>
# include <time.h>
# include <math.h>
# include </System/Library/Frameworks/Tk.framework/Versions/8.4/Headers/X11/X.h>
//# include <X11/X.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MARGIN 25
# define FPS 60
# define ANT_WIDTH 5
# define START_WIDTH 7
# define POINT_SIZE 4
# define TIMER 1

typedef struct		s_timer
{
	clock_t			now;
	clock_t			last_time;
	double			delta;
	clock_t			timer;
	int				ticks;
	double			time_per_tick;
}					t_timer;

typedef struct			s_point
{
	int					x;
	int					y;
	int					start: 2;
	int					end: 2;
}						t_point;

typedef struct			s_list_point
{
	struct s_list_point	*next;
	char				*name;
	t_point				*point;
}						t_list_point;

typedef struct			s_list_edges
{
	struct s_list_edges	*next;
	char				*node1;
	char				*node2;
}						t_list_edges;

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
	t_list_edges		*head_edges;
	t_timer				*timer;
	int					min_x;
	int					max_x;
	int					min_y;
	int					max_y;
}						t_env;

void	draw_line(t_env *env, t_point *ini_point, t_point *final_point);
void	draw_edges(t_env *env);
void	draw_points(t_env *env);
void	give_coord(t_env *env);

void	draw_ant(t_env *env, t_point *point);
void	draw_start_end2(t_env *env, t_point *point);
void	draw_start_end(t_env *env);

void	update_game(t_env *env, char *line);

double	get_slope(double min, double max, double new_min, double new_max);
double	map(double nb, double min, double slope, double new_min);
void	my_clear_image(t_env *env);
void	find_min_max(t_env *env, t_list_point *list);

t_point	*get_point_in_list(t_env *env, char *name);
void	free_splitted(char **splitted);
void	get_input(t_env *env, char **line);

void		timer_init(t_timer *timer);
void		get_next_time(t_timer *timer);
void		reset_timer(t_timer *timer);

int		expose_hook(void *param);
int		exit_hook(void *param);

void	push_list(t_list_point **head, int x, int y, char *name);
void	push_edges(t_list_edges **head, char *node1, char *node2);

#endif
