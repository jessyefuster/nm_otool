/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 12:14:42 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/28 12:14:44 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	tab = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		tab[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		tab[len1 + i] = s2[i];
		i++;
	}
	tab[len1 + i] = '\0';
	return (tab);
}
