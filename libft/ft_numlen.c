/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:32:54 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/26 14:12:33 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_numlen(long value, int base)
{
	int		len;

	len = 0;
	while (value / base != 0)
	{
		value /= base;
		len++;
	}
	return (len + 1);
}
