/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 09:30:20 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/30 09:30:26 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmap(char *s, char (*f)(char))
{
	size_t	i;
	char	*str;

	str = ft_strdup(s);
	i = 0;
	while (str[i])
	{
		str[i] = (*f)(str[i]);
		i++;
	}
	return (str);
}
