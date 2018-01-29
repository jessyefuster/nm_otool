/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:09:28 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/26 16:22:41 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t len_dst;
	size_t j;
	size_t len_src;

	i = 0;
	j = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst > size)
		return (size + len_src);
	i = len_dst;
	while (i + j < size - 1 && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	if (src[j - 1] == '\0' || i + j < size - 1)
		return (i + j);
	else
		return (size);
}
