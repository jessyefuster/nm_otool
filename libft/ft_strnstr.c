/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 02:18:25 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/27 02:18:28 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (s2[0] == '\0')
		return ((char *)s1);
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		j = i;
		k = 0;
		while (s1[j] == s2[k] && j < n)
		{
			j++;
			k++;
			if (s2[k] == '\0')
				return ((char *)s1 + i);
		}
		i++;
	}
	return (NULL);
}
