/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:13:50 by jpriou            #+#    #+#             */
/*   Updated: 2018/02/27 16:15:03 by jpriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countchar(char *str, char c)
{
	int		res;

	res = 0;
	if (str == 0)
		return (0);
	while (*str)
	{
		if (*str == c)
			res++;
		str++;
	}
	return (res);
}
