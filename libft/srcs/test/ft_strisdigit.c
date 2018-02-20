/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 10:07:45 by gmonnier          #+#    #+#             */
/*   Updated: 2018/02/19 10:32:42 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strisdigit(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '-' && *str != '+')
			return (0);
		str++;
	}
	return (1);
}