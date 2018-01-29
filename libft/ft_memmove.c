/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 04:12:31 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/27 04:12:39 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int		i;
	unsigned char		*str;
	unsigned char		*strsrc;

	str = (unsigned char *)dst;
	strsrc = (unsigned char *)src;
	if (dst <= src)
	{
		i = 0;
		while (i < len)
		{
			str[i] = strsrc[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			i--;
			str[i] = strsrc[i];
		}
	}
	return (dst);
}
