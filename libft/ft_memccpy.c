/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:05:35 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/26 14:27:33 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int		i;
	unsigned char		*dst_str;
	unsigned char		*src_str;

	dst_str = (unsigned char *)dst;
	src_str = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_str[i] = src_str[i];
		if (src_str[i] == (unsigned char)c)
			return ((void *)(dst_str + i + 1));
		i++;
	}
	return (NULL);
}
