/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:12:50 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/19 11:31:38 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_graphics.h"

void	get_edges(t_env *env, char **line)
{
	char		**splitted;

	do
	{
		if (*line[0] == '\0')
			break ;
		if (*line[0] == '#')
			continue ;
		splitted = ft_strsplit(*line, '-');
		push_edges(&env->head_edges, splitted[0], splitted[1]);
		free_splitted(splitted);
		ft_memdel((void**)line);
	}while (get_next_line(0, line) > 0);
}

void	get_end_start(t_env *env, char **line)
{
	char	**splitted;
	int		code;

	code = 0;
	if (ft_strcmp(*line, "##start"))
		code = 1;
	ft_memdel((void**)line);
	get_next_line(0, line);
	splitted = ft_strsplit(*line, ' ');
	push_list(&env->head_points, ft_atoi(splitted[1]), ft_atoi(splitted[2]), splitted[0]);
	free_splitted(splitted);
	if (code == 1)
		env->head_points->point->start = 1;
	else
		env->head_points->point->end = 1;

}

void	get_input(t_env *env, char **line)
{
	char	**splitted;

	get_next_line(0, line);
	ft_memdel((void**)line);
	while (get_next_line(0, line) > 0)
	{
		if (strchr(*line, '-'))
			break ;
		if (*line[0] != '#')
		{
			splitted = ft_strsplit(*line, ' ');
			push_list(&env->head_points, ft_atoi(splitted[1]), ft_atoi(splitted[2]), splitted[0]);
			free_splitted(splitted);
		}
		else if (ft_strcmp(*line, "##start") || ft_strcmp(*line, "##end"))
			get_end_start(env, line);
		ft_memdel((void**)line);
	}
	get_edges(env, line);
}
