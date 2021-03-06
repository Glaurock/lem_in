/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fauconfan <fauconfan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 23:51:19 by fauconfan         #+#    #+#             */
/*   Updated: 2018/02/15 23:54:41 by fauconfan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			my_ceil(int num, int den)
{
	if (num % den == 0)
		return (num / den);
	return (num / den + 1);
}
