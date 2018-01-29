/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 09:30:56 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/30 09:31:00 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

/*
** ligne 22 - 23 : while (++i - 1 < len - len_start - len_end)
** 						tab[i - 1] = s[len_start + i - 1];
**				POUR FUCKING NORME
**					while (i < len - len_start - len_end)
** 						tab[i] = s[len_start + i];
**						i++;
*/

char		*ft_strtrim(char const *s)
{
	size_t	len_start;
	size_t	len_end;
	size_t	i;
	size_t	len;
	char	*tab;

	len = ft_strlen(s);
	i = 0;
	len_start = 0;
	while (ft_isspace(s[i]))
		i++;
	len_start = i;
	i = len - 1;
	len_end = 0;
	while (ft_isspace(s[i]) && i > len_start)
		i--;
	len_end = len - 1 - i;
	tab = (char *)malloc(sizeof(char) * (len - len_start - len_end + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (++i - 1 < len - len_start - len_end)
		tab[i - 1] = s[len_start + i - 1];
	tab[i] = '\0';
	return (tab);
}
