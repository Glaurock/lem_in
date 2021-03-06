/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fauconfan <fauconfan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 10:07:45 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/20 18:38:14 by fauconfan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strisdigit(char *str)
{
	if (str == 0)
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}
