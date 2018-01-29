/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:05:35 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/26 14:27:33 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int		i;
	unsigned char		*str;
	unsigned char		*strsrc;

	str = (unsigned char *)dst;
	strsrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		str[i] = strsrc[i];
		i++;
	}
	return (dst);
}
