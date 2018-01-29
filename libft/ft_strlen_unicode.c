/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_unicode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfuster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:32:54 by jfuster           #+#    #+#             */
/*   Updated: 2015/11/26 14:12:33 by jfuster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_strlen_unicode(wchar_t *str)
{
	int		len;

	len = 0;
	while (*str)
	{
		if ((unsigned int)*str < 2048)
			len += 2;
		else if ((unsigned int)*str < 65536)
			len += 3;
		else if ((unsigned int)*str < 1114112)
			len += 4;
		str++;
	}
	return (len);
}
